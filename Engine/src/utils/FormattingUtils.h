#pragma once

#include "containers/BeString.h"
#include "core/Defines.h"
#include "math/Math.h"
#include "TypeUtils.h"

namespace BE {
template<FloatingPoint T_>
String FloatToString(T_ value_, u32 presicion = 4) {
  using T     = typename RemoveConst<T_>::Type;
  T value     = Math::Round(value_, presicion);
  b8 negative = value < 0;
  T abs       = negative ? -value : value;
  u32 digits  = abs > 0 ? (u32)Math::Log10(abs) + 1 : 1;

  String result(digits + negative + presicion + 1);

  for (u32 i{0}; i < digits; ++i) {
    result[digits - i - 1 + negative]  = '0' + ((i64)abs % 10);
    abs                               /= 10;
  }

  if (negative) {
    result[0] = '-';
  }

  result[digits + negative] = '.';
  abs                       = value - (T)(i64)value;
  for (u32 i{0}; i < presicion; ++i) {
    abs                               *= 10;
    result[digits + negative + i + 1]  = '0' + ((i64)abs % 10);
  }

  result.Resize(digits + negative + presicion + 1);
  return result;
}

template<UnsignedInteger T_>
String ToHex(T_ value, u32 padding = 0) {
  u32 digits = value == 0 ? 1 : (u32)Math::Log2((f32)value) / 4 + 1;
  digits     = Math::Max(digits, padding);
  String result(digits);

  for (u32 i = 0; i < digits; ++i) {
    result[digits - i - 1]   = "0123456789ABCDEF"[value & 0xF];
    value                  >>= 4;
  }

  result.Resize(digits);
  return result;
}

template<Pointer T_>
String ToHex(T_ value, u32 padding = 0) {
  u64 address = (u64)value;
  return ToHex(address, padding);
}

template<UnsignedInteger T_>
String ToBinary(T_ value, u32 padding = 0) {
  u32 digits = value == 0 ? 1 : (u32)Math::Log2((f32)value) + 1;
  digits     = Math::Max(digits, padding);
  String result(digits);

  for (u32 i = 0; i < digits; ++i) {
    result[digits - i - 1]   = '0' + (value & 1);
    value                  >>= 1;
  }

  result.Resize(digits);
  return result;
}

} // namespace BE
