#ifndef WIZ_ARG_TOKEN_HPP
#define WIZ_ARG_TOKEN_HPP
#pragma once

#include <print>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>

#include "wiz/cmd/arg/arg_token_define.hpp"
#include "wiz/cmd/arg/arg_token_equal.hpp"
#include "wiz/cmd/arg/arg_token_include.hpp"
#include "wiz/cmd/arg/arg_token_space.hpp"
#include "wiz/cmd/arg/arg_token_text.hpp"
#include "wiz/cmd/arg/arg_token_type.hpp"
#include "wiz/type.hpp"

namespace wiz
{
	using arg_token = std::variant<arg_token_equal, arg_token_define, arg_token_include, arg_token_space, arg_token_text>;

	namespace detail
	{
		[[nodiscard]] static constexpr arg_token_type token_type(arg_token const &token) noexcept
		{
			return std::visit([](auto const &arg) -> arg_token_type
												{
								using T = std::decay_t<decltype(arg)>;
								if constexpr (std::is_same_v<T, arg_token_define>)
								{
										return arg_token_type::DEFINE;
								}
										else if constexpr (std::is_same_v<T, arg_token_include>)
								{
										return arg_token_type::INCLUDE;
								}
								else if constexpr (std::is_same_v<T, arg_token_space>)
								{
										return arg_token_type::SPACE;
								}
								else if constexpr (std::is_same_v<T, arg_token_text>)
								{
										return arg_token_type::TEXT;
								}
								else if constexpr (std::is_same_v<T, arg_token_equal>)
								{
										return arg_token_type::EQUAL;
								}
								else
								{
										static_assert(false, "non-exhaustive visitor");
								} },
												token);
		}

		[[nodiscard]] static constexpr std::string_view token_type_str(arg_token const &token) noexcept
		{
			return std::visit([](auto const &arg) -> std::string_view
												{
								using T = std::decay_t<decltype(arg)>;
								if constexpr (std::is_same_v<T, arg_token_define>)
								{
										return "DEFINE";
								}
										else if constexpr (std::is_same_v<T, arg_token_include>)
								{
										return "INCLUDE";
								}
								else if constexpr (std::is_same_v<T, arg_token_space>)
								{
										return "SPACE";
								}
								else if constexpr (std::is_same_v<T, arg_token_text>)
								{
										return "TEXT";
								}
								else if constexpr (std::is_same_v<T, arg_token_equal>)
								{
										return "EQUAL";
								}
								else
								{
										static_assert(false, "non-exhaustive visitor");
								} },
												token);
		}

		static constexpr void token_set_end(arg_token &token, u32 end) noexcept
		{
			std::visit([e = end](auto &arg)
								 { arg.end() = e; }, token);
		}

		static constexpr u32 const &token_get_argv_index(arg_token const &token) noexcept
		{
			return std::visit([](auto const &arg) -> u32 const &
												{ return arg.argv_index(); }, token);
		}

		void token_print(arg_token const &token) noexcept
		{
			std::visit([](auto const &arg)
								 { return std::print("{} {}[{}-{}]\n", token_type_str(arg), arg.argv_index(), arg.begin(), arg.end()); },
								 token);
		}

		[[nodiscard]] static constexpr std::pair<b8, usize> token_start_with(std::string_view const &buffer, arg_token_type type) noexcept
		{
			switch (type)
			{
			case arg_token_type::NONE:
				return std::pair<b8, usize>{false, 0UL};
			case arg_token_type::SPACE:
				for (std::string_view const &signature : arg_token_space::SIGNATURES)
				{
					if (buffer.starts_with(signature))
					{
						return std::pair<b8, usize>{true, signature.size()};
					}
				}
				break;
			[[likely]] case arg_token_type::TEXT:
				return std::pair<b8, usize>{true, 1UL};
			case arg_token_type::DEFINE:
				for (std::string_view const &signature : arg_token_define::SIGNATURES)
				{
					if (buffer.starts_with(signature))
					{
						return std::pair<b8, usize>{true, signature.size()};
					}
				}
				break;
			case arg_token_type::INCLUDE:
				for (std::string_view const &signature : arg_token_include::SIGNATURES)
				{
					if (buffer.starts_with(signature))
					{
						return std::pair<b8, usize>{true, signature.size()};
					}
				}
				break;
			case arg_token_type::EQUAL:
				for (std::string_view const &signature : arg_token_equal::SIGNATURES)
				{
					if (buffer.starts_with(signature))
					{
						return std::pair<b8, usize>{true, signature.size()};
					}
				}
				break;
			}
			return std::pair<b8, usize>{false, 0UL};
		}
	}

}

#endif // WIZ_ARG_TOKEN_HPP