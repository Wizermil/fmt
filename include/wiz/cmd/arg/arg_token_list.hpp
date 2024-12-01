#ifndef WIZ_ARG_TOKEN_LIST_HPP
#define WIZ_ARG_TOKEN_LIST_HPP
#pragma once

#include <algorithm>
#include <initializer_list>
#include <utility>
#include <vector>

#include "wiz/cmd/arg/arg_token.hpp"
#include "wiz/type.hpp"

namespace wiz
{
	using arg_token_list = std::vector<arg_token>;

	static constexpr usize TOKEN_BUFFER_SIZE = std::max({arg_token_equal::SIGNATURES_MAX_SIZE,
																											 arg_token_define::SIGNATURES_MAX_SIZE,
																											 arg_token_include::SIGNATURES_MAX_SIZE,
																											 arg_token_space::SIGNATURES_MAX_SIZE,
																											 arg_token_text::SIGNATURES_MAX_SIZE});

	namespace detail
	{
		static constexpr void token_list_add(arg_token_list &tokens, arg_token_type type, u32 argv_index, u32 beg, u32 end) noexcept
		{
			switch (type)
			{
			case arg_token_type::NONE:
				break;
			case arg_token_type::SPACE:
				tokens.emplace_back(std::in_place_type_t<arg_token_space>(), argv_index, beg, end);
				break;
			[[likely]] case arg_token_type::TEXT:
				tokens.emplace_back(std::in_place_type_t<arg_token_text>(), argv_index, beg, end);
				break;
			case arg_token_type::DEFINE:
				tokens.emplace_back(std::in_place_type_t<arg_token_define>(), argv_index, beg, end);
				break;
			case arg_token_type::INCLUDE:
				tokens.emplace_back(std::in_place_type_t<arg_token_include>(), argv_index, beg, end);
				break;
			case arg_token_type::EQUAL:
				tokens.emplace_back(std::in_place_type_t<arg_token_equal>(), argv_index, beg, end);
				break;
			}
		}

		static constexpr void token_list_add_or_set_end_previous(arg_token_list &tokens, arg_token_type type, u32 argv_index, u32 beg, u32 end) noexcept
		{
			if (!tokens.empty()) [[likely]]
			{
				arg_token &previous_token = tokens.back();
				if (token_type(previous_token) == type && token_get_argv_index(previous_token) == argv_index) [[unlikely]]
				{
					token_set_end(previous_token, end);
				}
				else
				{
					token_list_add(tokens, type, argv_index, beg, end);
				}
			}
			else
			{
				token_list_add(tokens, type, argv_index, beg, end);
			}
		}
	}
}

#endif // WIZ_ARG_TOKEN_LIST_HPP
