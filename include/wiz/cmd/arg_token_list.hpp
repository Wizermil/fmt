#ifndef WIZ_ARG_TOKEN_LIST_HPP
#define WIZ_ARG_TOKEN_LIST_HPP
#pragma once

#include <variant>
#include <vector>

#include "wiz/cmd/arg_token_d.hpp"
#include "wiz/cmd/arg_token_dash.hpp"
#include "wiz/cmd/arg_token_equal.hpp"
#include "wiz/cmd/arg_token_i.hpp"
#include "wiz/cmd/arg_token_space.hpp"
#include "wiz/cmd/arg_token_text.hpp"
#include "wiz/type.hpp"

namespace wiz
{
	using arg_token = std::variant<arg_token_dash, arg_token_space, arg_token_text, arg_token_i, arg_token_d, arg_token_equal>;
	using arg_token_list = std::vector<arg_token>;
}

#endif // WIZ_ARG_TOKEN_LIST_HPP
