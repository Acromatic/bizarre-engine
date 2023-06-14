#pragma once

using c8  = char;
using c16 = char16_t;
using c32 = char32_t;

using i8  = char;
using i16 = short;
using i32 = int;
using i64 = long long;

using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

using b8  = bool;
using b32 = int;

using byte = u8;

using be_size = u64;

using BeFlags = u64;

#define BIT(x) (1 << (x))

static_assert(sizeof(c8) == 1, "c8 must be 1 byte");
static_assert(sizeof(c16) == 2, "c16 must be 2 bytes");
static_assert(sizeof(c32) == 4, "c32 must be 4 bytes");

static_assert(sizeof(i8) == 1, "i8 must be 1 byte");
static_assert(sizeof(i16) == 2, "i16 must be 2 bytes");
static_assert(sizeof(i32) == 4, "i32 must be 4 bytes");
static_assert(sizeof(i64) == 8, "i64 must be 8 bytes");

static_assert(sizeof(u8) == 1, "u8 must be 1 byte");
static_assert(sizeof(u16) == 2, "u16 must be 2 bytes");
static_assert(sizeof(u32) == 4, "u32 must be 4 bytes");
static_assert(sizeof(u64) == 8, "u64 must be 8 bytes");

static_assert(sizeof(f32) == 4, "f32 must be 4 bytes");
static_assert(sizeof(f64) == 8, "f64 must be 8 bytes");

static_assert(sizeof(b8) == 1, "b8 must be 1 byte");
static_assert(sizeof(b32) == 4, "b32 must be 4 bytes");

static_assert(sizeof(byte) == 1, "byte must be 1 byte");

static_assert(sizeof(BeFlags) == 8, "BeFlags must be 8 bytes");

#if defined(_WIN32)
  #define BE_PLATFORM_WINDOWS
  #if !defined(_WIN64)
    #error "64-bit is required"
  #endif
#elif defined(__linux__)
  #define BE_PLATFORM_LINUX
#elif defined(__APPLE__)
  #define BE_PLATFORM_MACOS
#else
  #error "Unknown platform"
#endif

#if defined(BE_PLATFORM_WINDOWS)
  #define BE_DEBUG_BREAK() __debugbreak()
#elif defined(BE_PLATFORM_LINUX)
  #define BE_DEBUG_BREAK() __builtin_trap()
#elif defined(BE_PLATFORM_MACOS)
  #define BE_DEBUG_BREAK() __builtin_trap()
#endif
