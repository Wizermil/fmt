#ifndef WIZ_CMD_INPUT_HPP
#define WIZ_CMD_INPUT_HPP
#pragma once

#include <string>

namespace wiz
{
	class cmd_input
	{
		std::string _path;

	public:
		constexpr cmd_input() noexcept = default;
		constexpr cmd_input(cmd_input const &) noexcept = default;
		constexpr cmd_input &operator=(cmd_input const &) noexcept = default;
		constexpr cmd_input(cmd_input &&) noexcept = default;
		constexpr cmd_input &operator=(cmd_input &&) noexcept = default;
		constexpr ~cmd_input() noexcept = default;

		explicit constexpr cmd_input(std::string const &str) noexcept : _path(str) {}
	};
}

#endif // WIZ_CMD_INPUT_HPP