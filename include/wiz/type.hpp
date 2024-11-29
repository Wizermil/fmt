#ifndef WIZ_TYPE_HPP
#define WIZ_TYPE_HPP
#pragma once

using b8 = bool;

using c8 = char;
using c16 = char16_t;
using c32 = char32_t;

using s8 = signed char;
using u8 = unsigned char;
using s16 = signed short int;
using u16 = unsigned short int;
using s32 = signed int;
using u32 = unsigned int;
using s64 = signed long long int;
using u64 = unsigned long long int;

using usize = unsigned long int;
using ssize = signed long int;

#if defined(__SIZEOF_INT128__)
using u128 = __uint128_t;
using s128 = __int128_t;
#endif

using f32 = float;
using f64 = double;

static_assert(sizeof(b8) == 1, "b8 must be 8 bits");

static_assert(sizeof(c8) == 1, "c8 must be 8 bits");
static_assert(sizeof(c16) == 2, "c16 must be 16 bits");
static_assert(sizeof(c32) == 4, "c32 must be 32 bits");

static_assert(sizeof(s8) == 1, "s8 must be 8 bits");
static_assert(sizeof(u8) == 1, "u8 must be 8 bits");
static_assert(sizeof(s16) == 2, "s16 must be 16 bits");
static_assert(sizeof(u16) == 2, "u16 must be 16 bits");
static_assert(sizeof(s32) == 4, "s32 must be 32 bits");
static_assert(sizeof(u32) == 4, "u32 must be 32 bits");
static_assert(sizeof(s64) == 8, "s64 must be 64 bits");
static_assert(sizeof(u64) == 8, "u64 must be 64 bits");

#if defined(__LP64__) || defined(__aarch64__) || (defined(__x86_64__) && !defined(__ILP32__))
static_assert(sizeof(usize) == 8, "usize must be 64 bits");
static_assert(sizeof(ssize) == 8, "ssize must be 64 bits");
#else
static_assert(sizeof(usize) == 4, "usize must be 32 bits");
static_assert(sizeof(ssize) == 4, "ssize must be 32 bits");
#endif

static_assert(sizeof(f32) == 4, "f32 must be 32 bits");
static_assert(sizeof(f64) == 8, "f64 must be 64 bits");

#if defined(__SIZEOF_INT128__)
static_assert(sizeof(u128) == 16, "u128 must be 128 bits");
static_assert(sizeof(s128) == 16, "s128 must be 128 bits");
#endif

#endif // WIZ_TYPE_HPP