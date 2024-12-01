#ifndef WIZ_ARG_TOKEN_INCLUDE_HPP
#define WIZ_ARG_TOKEN_INCLUDE_HPP
#pragma once

#include <algorithm>
#include <array>
#include <initializer_list>
#include <string_view>

#include "wiz/type.hpp"

namespace wiz
{

	class arg_token_include
	{
		u32 _argv_index = 0U;
		u32 _beg = 0U;
		u32 _end = 0UL;

	public:
		static constexpr std::array<std::string_view, 2UL> SIGNATURES{
				"-I",
				"--include-directory"};
		static constexpr usize SIGNATURES_MAX_SIZE = std::max({SIGNATURES[0].size(), SIGNATURES[1].size()});

	public:
		constexpr arg_token_include() noexcept = default;
		constexpr arg_token_include(arg_token_include const &) noexcept = default;
		constexpr arg_token_include &operator=(arg_token_include const &) noexcept = default;
		constexpr arg_token_include(arg_token_include &&) noexcept = default;
		constexpr arg_token_include &operator=(arg_token_include &&) noexcept = default;
		constexpr ~arg_token_include() noexcept = default;

		explicit constexpr arg_token_include(u32 argv_index, u32 beg, u32 end) : _argv_index(argv_index), _beg(beg), _end(end) {}

		[[nodiscard]] constexpr u32 &argv_index() noexcept { return _argv_index; }
		[[nodiscard]] constexpr u32 const &argv_index() const noexcept { return _argv_index; }
		[[nodiscard]] constexpr u32 &begin() noexcept { return _beg; }
		[[nodiscard]] constexpr u32 const &begin() const noexcept { return _beg; }
		[[nodiscard]] constexpr u32 &end() noexcept { return _end; }
		[[nodiscard]] constexpr u32 const &end() const noexcept { return _end; }
	};
}

#endif // WIZ_ARG_TOKEN_INCLUDE_HPP
