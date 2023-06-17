#pragma once

#include <core/Defines.h>
#include <type_traits>

namespace BE {

struct TrueType {
  static constexpr bool Value = true;
};

struct FalseType {
  static constexpr bool Value = false;
};

template<typename T>
struct IsPointer : public FalseType {};

template<typename T>
struct IsPointer<T*> : public TrueType {};

template<typename T>
struct IsPointer<T* const> : public TrueType {};

template<typename T>
struct IsReference : public FalseType {};

template<typename T>
struct IsReference<T&> : public TrueType {};

template<typename T>
struct IsReference<T&&> : public TrueType {};

template<typename T>
struct TypeIdentity {
  using Type = T;
};

template<typename T>
struct TypeIdentity<T&> {
  using Type = T;
};

template<typename T>
struct TypeIdentity<T&&> {
  using Type = T;
};

template<typename T>
using TypeIdentityT = typename TypeIdentity<T>::Type;

template<typename T>
T&& Forward(TypeIdentityT<T>& t) {
  return static_cast<T&&>(t);
}

template<typename T>
T&& Forward(TypeIdentityT<T>&& t) {
  return static_cast<T&&>(t);
}

template<typename T>
constexpr T&& Move(TypeIdentityT<T>& t) {
  return static_cast<T&&>(t);
}

template<typename T>
constexpr T&& Move(TypeIdentityT<T>&& t) {
  return static_cast<T&&>(t);
}

template<typename T, typename U>
struct IsSame : public FalseType {};

template<typename T>
struct IsSame<T, T> : public TrueType {};

} // namespace BE
