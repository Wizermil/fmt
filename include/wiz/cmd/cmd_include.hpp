#ifndef WIZ_CMD_INCLUDE_HPP
#define WIZ_CMD_INCLUDE_HPP
#pragma once

#include <string>

namespace wiz
{
	class cmd_include
	{
		std::string _path;

	public:
		constexpr cmd_include() noexcept = default;
		constexpr cmd_include(cmd_include const &) noexcept = default;
		constexpr cmd_include &operator=(cmd_include const &) noexcept = default;
		constexpr cmd_include(cmd_include &&) noexcept = default;
		constexpr cmd_include &operator=(cmd_include &&) noexcept = default;
		constexpr ~cmd_include() noexcept = default;

		explicit constexpr cmd_include(std::string const &str) noexcept : _path(str) {}
	};
}

#endif // WIZ_CMD_INCLUDE_HPP