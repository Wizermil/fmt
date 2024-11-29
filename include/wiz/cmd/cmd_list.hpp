#ifndef WIZ_ARG_LIST_HPP
#define WIZ_ARG_LIST_HPP
#pragma once

#include <print>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "wiz/cmd/arg_token_d.hpp"
#include "wiz/cmd/arg_token_dash.hpp"
#include "wiz/cmd/arg_token_equal.hpp"
#include "wiz/cmd/arg_token_i.hpp"
#include "wiz/cmd/arg_token_list.hpp"
#include "wiz/cmd/arg_token_space.hpp"
#include "wiz/cmd/arg_token_text.hpp"
#include "wiz/cmd/arg_token_type.hpp"
#include "wiz/cmd/cmd_include.hpp"
#include "wiz/cmd/cmd_input.hpp"
#include "wiz/cmd/cmd_output.hpp"
#include "wiz/type.hpp"

namespace wiz
{
    namespace detail
    {
        static constexpr b8 add_token(arg_token_list &tokens, arg_token_type from_type, arg_token_type to_type, u32 argv_index, u32 beg, u32 end) noexcept
        {
            b8 ret = false;
            if (from_type == arg_token_type::NONE) [[unlikely]]
            {
                ret = true;
            }
            else if (from_type != to_type)
            {
                switch (from_type)
                {
                case arg_token_type::NONE:
                    break;
                case arg_token_type::DASH:
                    tokens.emplace_back(std::in_place_type_t<arg_token_dash>(), argv_index, beg, end);
                    ret = true;
                    break;
                case arg_token_type::SPACE:
                    tokens.emplace_back(std::in_place_type_t<arg_token_space>(), argv_index, beg, end);
                    ret = true;
                    break;
                [[likely]] case arg_token_type::TEXT:
                    tokens.emplace_back(std::in_place_type_t<arg_token_text>(), argv_index, beg, end);
                    ret = true;
                    break;
                case arg_token_type::I:
                    tokens.emplace_back(std::in_place_type_t<arg_token_i>(), argv_index, beg, end);
                    ret = true;
                    break;
                case arg_token_type::D:
                    tokens.emplace_back(std::in_place_type_t<arg_token_d>(), argv_index, beg, end);
                    ret = true;
                    break;
                case arg_token_type::EQUAL:
                    tokens.emplace_back(std::in_place_type_t<arg_token_equal>(), argv_index, beg, end);
                    ret = true;
                    break;
                }
            }
            return ret;
        }

        static constexpr arg_token_type token_type(arg_token const &token) noexcept
        {
            return std::visit([](auto const &arg) -> arg_token_type
                              {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, arg_token_dash>)
                {
                    return arg_token_type::DASH;
                }
                else if constexpr (std::is_same_v<T, arg_token_space>)
                {
                    return arg_token_type::SPACE;
                }
                else if constexpr (std::is_same_v<T, arg_token_text>)
                {
                    return arg_token_type::TEXT;
                }
                else if constexpr (std::is_same_v<T, arg_token_i>)
                {
                    return arg_token_type::I;
                }
                else if constexpr (std::is_same_v<T, arg_token_d>)
                {
                    return arg_token_type::D;
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
    }

    class cmd_list
    {
        using cmd = std::variant<std::monostate, cmd_include, cmd_input, cmd_output>;
        std::vector<cmd> _cmds;

    public:
        constexpr cmd_list() noexcept = default;
        constexpr cmd_list(cmd_list const &) noexcept = default;
        constexpr cmd_list &operator=(cmd_list const &) noexcept = default;
        constexpr cmd_list(cmd_list &&) noexcept = default;
        constexpr cmd_list &operator=(cmd_list &&) noexcept = default;
        constexpr ~cmd_list() noexcept = default;

        explicit constexpr cmd_list(u32 argc, c8 const **argv)
        {
            for (usize argv_index = 1UL; argv_index < argc; ++argv_index) [[likely]]
            {
                arg_token_list tokens;
                arg_token_type token_type = arg_token_type::NONE;
                u32 token_cursor = 0UL;
                u32 token_beg = 0UL;
                c8 const *arg_str_c = argv[argv_index];

                for (c8 c = *arg_str_c; c != '\0'; c = *(++arg_str_c), ++token_cursor) [[likely]]
                {
                    if (c == '-')
                    {
                        if (detail::add_token(tokens, token_type, arg_token_type::DASH, argv_index, token_beg, token_cursor)) [[likely]]
                        {
                            token_type = arg_token_type::DASH;
                            token_beg = token_cursor;
                        }
                    }
                    else if (c == ' ')
                    {
                        if (detail::add_token(tokens, token_type, arg_token_type::SPACE, argv_index, token_beg, token_cursor))
                        {
                            token_type = arg_token_type::SPACE;
                            token_beg = token_cursor;
                        }
                    }
                    else if (c == 'I')
                    {
                        if (detail::add_token(tokens, token_type, arg_token_type::I, argv_index, token_beg, token_cursor))
                        {
                            token_type = arg_token_type::I;
                            token_beg = token_cursor;
                        }
                    }
                    else if (c == 'D')
                    {
                        if (detail::add_token(tokens, token_type, arg_token_type::D, argv_index, token_beg, token_cursor))
                        {
                            token_type = arg_token_type::D;
                            token_beg = token_cursor;
                        }
                    }
                    else if (c == '=')
                    {
                        if (detail::add_token(tokens, token_type, arg_token_type::EQUAL, argv_index, token_beg, token_cursor))
                        {
                            token_type = arg_token_type::EQUAL;
                            token_beg = token_cursor;
                        }
                    }
                    else
                    {
                        if (detail::add_token(tokens, token_type, arg_token_type::TEXT, argv_index, token_beg, token_cursor))
                        {
                            token_type = arg_token_type::TEXT;
                            token_beg = token_cursor;
                        }
                    }
                }
                if (token_beg != token_cursor)
                {
                    detail::add_token(tokens, token_type, arg_token_type::NONE, argv_index, token_beg, token_cursor);
                }

                if (!tokens.empty()) [[likely]]
                {
                    // trim spaces
                    auto first = tokens.begin();
                    if (detail::token_type(*first) == arg_token_type::SPACE)
                    {
                        tokens.erase(first);
                    }
                    if (!tokens.empty()) [[likely]]
                    {
                        auto last = tokens.end() - 1UL;
                        if (detail::token_type(*last) == arg_token_type::SPACE)
                        {
                            tokens.erase(last);
                        }
                    }
                    for (arg_token const &token : tokens)
                    {
                    }
                }
            }
        }
    };
}

#endif // WIZ_ARG_LIST_HPP