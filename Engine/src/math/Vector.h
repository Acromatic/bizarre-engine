#pragma once

#include "core/Defines.h"

#include <initializer_list>

namespace BE {

template<typename T, u64 N>
union Vector {
  Vector()                    = default;
  Vector(const Vector& other) = default;
  Vector(Vector&& other)      = default;

  Vector& operator=(const Vector& other) = default;
  Vector& operator=(Vector&& other)      = default;

  template<typename... Args>
  Vector(Args... args) : data{args...} {}

  T data[N];
};

template<typename T>
union Vector<T, 2> {
  Vector()                    = default;
  Vector(const Vector& other) = default;
  Vector(Vector&& other)      = default;

  Vector& operator=(const Vector& other) = default;
  Vector& operator=(Vector&& other)      = default;

  template<typename... Args>
  Vector(Args... args) : data{args...} {}

  T data[2];

  struct {
    T x;
    T y;
  };
};

template<typename T>
union Vector<T, 3> {
  Vector()                    = default;
  Vector(const Vector& other) = default;
  Vector(Vector&& other)      = default;

  Vector& operator=(const Vector& other) = default;
  Vector& operator=(Vector&& other)      = default;

  template<typename... Args>
  Vector(Args... args) : data{args...} {}

  T data[3];

  struct {
    T x;
    T y;
    T z;
  };

  struct {
    T r;
    T g;
    T b;
  };
};

template<typename T>
union Vector<T, 4> {
  Vector()                    = default;
  Vector(const Vector& other) = default;
  Vector(Vector&& other)      = default;

  Vector& operator=(const Vector& other) = default;
  Vector& operator=(Vector&& other)      = default;

  template<typename... Args>
  Vector(Args... args) : data{args...} {}

  T data[4];

  struct {
    T x;
    T y;
    T z;
    T w;
  };

  struct {
    T r;
    T g;
    T b;
    T a;
  };
};

using Vec2 = Vector<f32, 2>;

using Vec3 = Vector<f32, 3>;
using Vec4 = Vector<f32, 4>;

using Vec2i = Vector<i32, 2>;
using Vec3i = Vector<i32, 3>;
using Vec4i = Vector<i32, 4>;

using Vec2u = Vector<u32, 2>;
using Vec3u = Vector<u32, 3>;
using Vec4u = Vector<u32, 4>;

} // namespace BE
