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
concept Pointer = IsPointer<T>::Value;

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
struct RemoveConst {
  using Type = T;
};

template<typename T>
struct RemoveConst<const T> {
  using Type = T;
};

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

template<typename T, typename U>
constexpr b8 IsSameV = IsSame<T, U>::Value;

template<typename T, typename U>
concept Same = IsSameV<T, U>;

template<typename From, typename To>
concept ConvertibleTo =
    IsSameV<From, To> || requires(TypeIdentityT<From>&& t) { static_cast<TypeIdentityT<To>>(t); };

template<typename T, typename... Args>
concept ConstructibleFrom = requires(Args&&... args) { T{Forward<Args>(args)...}; };

template<typename T>
struct IsIntegral : public FalseType {};

template<typename T>
  requires ConvertibleTo<T, i64> && ConvertibleTo<T, u64> && (T{1} / T{2} == T{0})
struct IsIntegral<T> : public TrueType {};

template<typename T>
concept Integral = IsIntegral<T>::Value;

template<Integral T>
constexpr b8 IsSignedInteger() {
  return T{0} > (T{0} - T{1});
}

template<typename T>
concept UnsignedInteger = Integral<T> && !IsSignedInteger<T>();

template<typename T>
concept SignedInteger = Integral<T> && IsSignedInteger<T>();

template<typename T>
struct IsFloatingPoint : public FalseType {};

template<>
struct IsFloatingPoint<f32> : public TrueType {};

template<>
struct IsFloatingPoint<f64> : public TrueType {};

template<typename T>
concept FloatingPoint = IsFloatingPoint<T>::Value;

template<typename T>
concept Arithmetic = Integral<T> || FloatingPoint<T>;

} // namespace BE
