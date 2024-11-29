#ifndef WIZ_ARG_TOKEN_DASH_HPP
#define WIZ_ARG_TOKEN_DASH_HPP
#pragma once

#include "wiz/type.hpp"

namespace wiz
{
	class arg_token_dash
	{
		u32 _argv_index = 0U;
		u32 _beg = 0U;
		u32 _end = 0U;

	public:
		constexpr arg_token_dash() noexcept = default;
		constexpr arg_token_dash(arg_token_dash const &) noexcept = default;
		constexpr arg_token_dash &operator=(arg_token_dash const &) noexcept = default;
		constexpr arg_token_dash(arg_token_dash &&) noexcept = default;
		constexpr arg_token_dash &operator=(arg_token_dash &&) noexcept = default;
		constexpr ~arg_token_dash() noexcept = default;

		explicit constexpr arg_token_dash(u32 argv_index, u32 beg, u32 end) : _argv_index(argv_index), _beg(beg), _end(end) {}
	};
}

#endif // WIZ_ARG_TOKEN_DASH_HPP
