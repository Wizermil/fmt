#ifndef WIZ_ARG_TOKEN_I_HPP
#define WIZ_ARG_TOKEN_I_HPP
#pragma once

#include "wiz/type.hpp"

namespace wiz
{
	class arg_token_i
	{
		u32 _argv_index = 0U;
		u32 _beg = 0UL;
		u32 _end = 0UL;

	public:
		constexpr arg_token_i() noexcept = default;
		constexpr arg_token_i(arg_token_i const &) noexcept = default;
		constexpr arg_token_i &operator=(arg_token_i const &) noexcept = default;
		constexpr arg_token_i(arg_token_i &&) noexcept = default;
		constexpr arg_token_i &operator=(arg_token_i &&) noexcept = default;
		constexpr ~arg_token_i() noexcept = default;

		explicit constexpr arg_token_i(u32 argv_index, u32 beg, u32 end) : _argv_index(argv_index), _beg(beg), _end(end) {}
	};
}

#endif // WIZ_ARG_TOKEN_I_HPP
