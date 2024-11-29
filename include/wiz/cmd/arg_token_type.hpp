#ifndef WIZ_ARG_TOKEN_TYPE_HPP
#define WIZ_ARG_TOKEN_TYPE_HPP
#pragma once

#include <type_traits>

#include "wiz/type.hpp"

namespace wiz
{
    enum struct arg_token_type : u8
    {
        NONE = 0U,
        DASH = 1U << 1U,
        I = 1U << 2U,
        D = 1U << 3U,
        SPACE = 1U << 4U,
        EQUAL = 1U << 5U,
        TEXT = 1U << 6U
    };

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

    static constexpr u64 TOKEN_TYPE_BIT = sizeof(std::underlying_type_t<arg_token_type>) * __CHAR_BIT__;

    namespace detail
    {
        template <typename First, typename... Rest>
        consteval uint64_t generate_token_code(First arg0, Rest... args) noexcept
        {
            return (static_cast<uint64_t>(arg0) << (TOKEN_TYPE_BIT * sizeof...(args))) | generate_token_code(args...);
        }
        consteval u64 generate_token_code() noexcept
        {
            return 0ULL;
        }
    }

    static constexpr u64 TOKEN_INCLUDE_CODE = static_cast<u64>(arg_token_type::DASH) << TOKEN_TYPE_BIT | static_cast<u64>(arg_token_type::I);                                                                                       // -I
    static constexpr u64 TOKEN_DEFINE_CODE = static_cast<u64>(arg_token_type::DASH) << TOKEN_TYPE_BIT | static_cast<u64>(arg_token_type::D);                                                                                        // -D
    static constexpr u64 TOKEN_INCLUDE_DEFINE_LONG_CODE = static_cast<u64>(arg_token_type::DASH) << TOKEN_TYPE_BIT | static_cast<u64>(arg_token_type::TEXT);                                                                        // --include-directory | --define-macro
    static constexpr u64 TOKEN_INCLUDE_DEFINE_LONG_EQUAL_CODE = static_cast<u64>(arg_token_type::EQUAL) << TOKEN_TYPE_BIT * 2 | static_cast<u64>(arg_token_type::SPACE) << TOKEN_TYPE_BIT | static_cast<u64>(arg_token_type::TEXT); // --include-directory = FilePath | --define-macro = FilePath
    static constexpr u64 TEXT_DEFINE_CODE = static_cast<u64>(arg_token_type::TEXT);                                                                                                                                                 // File Path

    static_assert(detail::generate_token_code(arg_token_type::DASH, arg_token_type::I) == TOKEN_INCLUDE_CODE);
}

#endif // WIZ_ARG_TOKEN_TYPE_HPP