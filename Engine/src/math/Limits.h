#pragma once

#include "core/Defines.h"

namespace BE {
template<typename T>
struct Limits {
  static constexpr T Min() { return T(); }

  static constexpr T Max() { return T(); }

  static constexpr b8 IsSigned = false;
};

template<>
struct Limits<i8> {
  static constexpr i8 Min() { return -128; }

  static constexpr i8 Max() { return 127; }

  static constexpr b8 IsSigned = true;
};

template<>
struct Limits<i16> {
  static constexpr i16 Min() { return -32768; }

  static constexpr i16 Max() { return 32767; }

  static constexpr b8 IsSigned = true;
};

template<>
struct Limits<i32> {
  static constexpr i32 Min() { return -2147483648; }

  static constexpr i32 Max() { return 2147483647; }

  static constexpr b8 IsSigned = true;
};

template<>
struct Limits<i64> {
  static constexpr i64 Min() { return -9223372036854775807ll; }

  static constexpr i64 Max() { return 9223372036854775807ll; }

  static constexpr b8 IsSigned = true;
};

template<>
struct Limits<u8> {
  static constexpr u8 Min() { return 0; }

  static constexpr u8 Max() { return 255u; }

  static constexpr b8 IsSigned = false;
};

template<>
struct Limits<u16> {
  static constexpr u16 Min() { return 0; }

  static constexpr u16 Max() { return 65535u; }

  static constexpr b8 IsSigned = false;
};

template<>
struct Limits<u32> {
  static constexpr u32 Min() { return 0; }

  static constexpr u32 Max() { return 4294967295lu; }

  static constexpr b8 IsSigned = false;
};

template<>
struct Limits<u64> {
  static constexpr u64 Min() { return 0; }

  static constexpr u64 Max() { return 18446744073709551615llu; }

  static constexpr b8 IsSigned = false;
};

template<>
struct Limits<f32> {
  static constexpr f32 Min() { return -3.402823466e+38F; }

  static constexpr f32 Max() { return 3.402823466e+38F; }

  static constexpr b8 IsSigned = true;
};

template<>
struct Limits<f64> {
  static constexpr f64 Min() { return -1.7976931348623158e+308; }

  static constexpr f64 Max() { return 1.7976931348623158e+308; }

  static constexpr b8 IsSigned = true;
};

} // namespace BE
