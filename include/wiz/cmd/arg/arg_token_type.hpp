#ifndef WIZ_ARG_TOKEN_TYPE_HPP
#define WIZ_ARG_TOKEN_TYPE_HPP
#pragma once

#include <array>
#include <type_traits>

#include "wiz/type.hpp"

namespace wiz
{
	enum struct arg_token_type : u8
	{
		NONE = 0U,
		INCLUDE, // -I, --include-directory
		DEFINE,	 // -D, --define-macro
		SPACE,
		EQUAL, // =
		TEXT
	};

	static constexpr std::array<arg_token_type, 5UL> TOKEN_TYPE_LIST{
			arg_token_type::INCLUDE,
			arg_token_type::DEFINE,
			arg_token_type::SPACE,
			arg_token_type::EQUAL,
			arg_token_type::TEXT}; // TEXT must be the last one because it take anything

	constexpr arg_token_type operator&(arg_token_type a, arg_token_type b) noexcept
	{
		using T = std::underlying_type_t<arg_token_type>;
		return static_cast<arg_token_type>(static_cast<T>(a) & static_cast<T>(b));
	}
	constexpr arg_token_type operator|(arg_token_type a, arg_token_type b) noexcept
	{
		using T = std::underlying_type_t<arg_token_type>;
		return static_cast<arg_token_type>(static_cast<T>(a) | static_cast<T>(b));
	}
	constexpr arg_token_type &operator&=(arg_token_type &a, arg_token_type b) noexcept
	{
		a = (a & b);
		return a;
	}
	constexpr arg_token_type &operator|=(arg_token_type &a, arg_token_type b) noexcept
	{
		a = (a | b);
		return a;
	}
}

#endif // WIZ_ARG_TOKEN_TYPE_HPP