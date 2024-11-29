#ifndef WIZ_ARG_TOKEN_SPACE_HPP
#define WIZ_ARG_TOKEN_SPACE_HPP
#pragma once

#include "wiz/type.hpp"

namespace wiz
{
	class arg_token_space
	{
		u32 _argv_index = 0U;
		u32 _beg = 0UL;
		u32 _end = 0UL;

	public:
		constexpr arg_token_space() noexcept = default;
		constexpr arg_token_space(arg_token_space const &) noexcept = default;
		constexpr arg_token_space &operator=(arg_token_space const &) noexcept = default;
		constexpr arg_token_space(arg_token_space &&) noexcept = default;
		constexpr arg_token_space &operator=(arg_token_space &&) noexcept = default;
		constexpr ~arg_token_space() noexcept = default;

		explicit constexpr arg_token_space(u32 argv_index, u32 beg, u32 end) : _argv_index(argv_index), _beg(beg), _end(end) {}
	};
}

#endif // WIZ_ARG_TOKEN_SPACE_HPP