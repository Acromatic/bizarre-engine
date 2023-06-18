#include "Math.h"

namespace BE::Math {

f64 Log(f64 x) {
  return __builtin_log(x);
}

f64 Log2(f64 x) {
  return __builtin_log2(x);
}

f64 Log10(f64 x) {
  return __builtin_log10(x);
}

f64 LogN(f64 x, f64 base) {
  return __builtin_log(x) / __builtin_log(base);
}

f32 Log(f32 x) {
  return __builtin_logf(x);
}

f32 Log2(f32 x) {
  return __builtin_log2f(x);
}

f32 Log10(f32 x) {
  return __builtin_log10f(x);
}

f32 LogN(f32 x, f32 base) {
  return __builtin_logf(x) / __builtin_logf(base);
}

f64 Pow(f64 x, f64 power) {
  return __builtin_pow(x, power);
}

f32 Pow(f32 x, f32 power) {
  return __builtin_powf(x, power);
}

f64 Round(f64 x) {
  return __builtin_round(x);
}

f32 Round(f32 x) {
  return __builtin_roundf(x);
}

f64 Round(f64 x, be_size precision) {
  return (f64)((i64)(x * Pow(10.0, precision) + 0.5)) / Pow(10.0, precision);
}

f32 Round(f32 x, be_size precision) {
  return (f32)((i64)(x * Pow(10.0f, precision) + 0.5f)) / Pow(10.0f, precision);
}

} // namespace BE::Math
