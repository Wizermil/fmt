#ifndef WIZ_ARG_OUTPUT_HPP
#define WIZ_ARG_OUTPUT_HPP
#pragma once

#include <string>

namespace wiz
{
	class cmd_output
	{
		std::string _path;

	public:
		constexpr cmd_output() noexcept = default;
		constexpr cmd_output(cmd_output const &) noexcept = default;
		constexpr cmd_output &operator=(cmd_output const &) noexcept = default;
		constexpr cmd_output(cmd_output &&) noexcept = default;
		constexpr cmd_output &operator=(cmd_output &&) noexcept = default;
		constexpr ~cmd_output() noexcept = default;

		explicit constexpr cmd_output(std::string const &str) noexcept : _path(str) {}
	};
}

#endif // WIZ_ARG_OUTPUT_HPP