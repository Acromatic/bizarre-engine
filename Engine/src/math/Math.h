#pragma once

#include "utils/TypeUtils.h"

#include <core/Defines.h>

namespace BE::Math {
f64 Log(f64 x);
f64 Log2(f64 x);
f64 Log10(f64 x);
f64 LogN(f64 x, f64 base);

f32 Log(f32 x);
f32 Log2(f32 x);
f32 Log10(f32 x);
f32 LogN(f32 x, f32 base);

f64 Pow(f64 x, f64 power);

f32 Pow(f32 x, f32 power);

f64 Round(f64 x);
f64 Round(f64 x, be_size precision = 2);

f32 Round(f32 x);
f32 Round(f32 x, be_size precision = 2);

constexpr f64 PI =
    3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;
constexpr f64 E =
    2.71828182845904523536028747135266249775724709369995957496696762772407663035354759;

constexpr f32 PI_F =
    3.14159265358979323846264338327950288419716939937510582097494459230781640628620899f;
constexpr f32 E_F =
    2.71828182845904523536028747135266249775724709369995957496696762772407663035354759f;

template<Arithmetic T>
inline static constexpr T Abs(T value) {
  return value < 0 ? -value : value;
}

template<Arithmetic T>
inline static constexpr T Min(T a, T b) {
  return a < b ? a : b;
}

template<Arithmetic T>
inline static constexpr T Max(T a, T b) {
  return a > b ? a : b;
}

} // namespace BE::Math
