#ifndef WIZ_CMD_LIST_HPP
#define WIZ_CMD_LIST_HPP
#pragma once

#include <print>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "wiz/cmd/arg/arg_token_define.hpp"
#include "wiz/cmd/arg/arg_token_equal.hpp"
#include "wiz/cmd/arg/arg_token_include.hpp"
#include "wiz/cmd/arg/arg_token_list.hpp"
#include "wiz/cmd/arg/arg_token_space.hpp"
#include "wiz/cmd/arg/arg_token_text.hpp"
#include "wiz/cmd/arg/arg_token_type.hpp"
#include "wiz/cmd/cmd_include.hpp"
#include "wiz/cmd/cmd_input.hpp"
#include "wiz/cmd/cmd_output.hpp"
#include "wiz/type.hpp"

namespace wiz
{
	class cmd_list
	{
		using cmd = std::variant<std::monostate, cmd_include, cmd_input, cmd_output>;
		std::vector<cmd> _cmds;

	public:
		constexpr cmd_list() noexcept = default;
		constexpr cmd_list(cmd_list const &) noexcept = default;
		constexpr cmd_list &operator=(cmd_list const &) noexcept = default;
		constexpr cmd_list(cmd_list &&) noexcept = default;
		constexpr cmd_list &operator=(cmd_list &&) noexcept = default;
		constexpr ~cmd_list() noexcept = default;

		explicit constexpr cmd_list(u32 argc, c8 const **argv)
		{
			for (usize argv_index = 1UL; argv_index < argc; ++argv_index) [[likely]]
			{
				arg_token_list tokens;
				u32 token_beg = 0UL;
				c8 const *arg_str_c = argv[argv_index];
				c8 const *buffer_c = arg_str_c;
				usize buffer_c_sz = 1UL;

				while (*arg_str_c != '\0') [[likely]]
				{
					std::string_view buffer(buffer_c, buffer_c_sz);
					b8 is_end_of_argv = *(arg_str_c + 1UL) == '\0';
					if (buffer.size() == TOKEN_BUFFER_SIZE || is_end_of_argv)
					{
						do
						{
							for (arg_token_type token_type : TOKEN_TYPE_LIST)
							{
								auto const [start_with, token_signature_size]{detail::token_start_with(buffer, token_type)};
								if (start_with)
								{
									u32 token_end = token_beg + static_cast<u32>(token_signature_size);
									detail::token_list_add_or_set_end_previous(tokens, token_type, argv_index, token_beg, token_end);
									token_beg = token_end;
									// update buffer
									buffer_c += token_signature_size;
									buffer_c_sz -= token_signature_size;
									buffer = std::string_view(buffer_c, buffer_c_sz);
									break;
								}
							}
						} while (is_end_of_argv && !buffer.empty()); // process all tokens only if it's the latest buffer
					}
					++arg_str_c;
					++buffer_c_sz;
				}

				if (!tokens.empty()) [[likely]]
				{
					// trim leading and trailing spaces
					auto first = tokens.begin();
					if (detail::token_type(*first) == arg_token_type::SPACE)
					{
						tokens.erase(first);
					}
					if (!tokens.empty()) [[likely]]
					{
						auto last = tokens.end() - 1UL;
						if (detail::token_type(*last) == arg_token_type::SPACE)
						{
							tokens.erase(last);
						}
					}
					for (arg_token const &token : tokens)
					{
						detail::token_print(token);
					}
				}
			}
		}
	};
}

#endif // WIZ_CMD_LIST_HPP