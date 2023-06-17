#pragma once

#include "core/Defines.h"
#include "utils/TypeUtils.h"

namespace BE {
template<be_size Index_, typename T>
class TupleElement_ {
public:
  TupleElement_() = default;

  TupleElement_(const TupleElement_& other) : m_Value(other.m_Value) {}

  TupleElement_(TupleElement_&& other) : m_Value(Move<T>(other.m_Value)) {}

  TupleElement_(const T& value) : m_Value(value) {}

  TupleElement_(T&& value) : m_Value(Move<T>(value)) {}

  TupleElement_& operator=(const TupleElement_& other) {
    m_Value = other.m_Value;
    return *this;
  }

  TupleElement_& operator=(TupleElement_&& other) {
    m_Value = Move<T>(other.m_Value);
    return *this;
  }

  TupleElement_& operator=(const T& value) {
    m_Value = value;
    return *this;
  }

  T& Get() { return m_Value; }

private:
  T m_Value;
};

template<be_size Index_, typename T, typename... Ts>
struct ExtractTypeAt {
  using Type = typename ExtractTypeAt<Index_ - 1, Ts...>::Type;
};

template<typename T, typename... Ts>
struct ExtractTypeAt<0, T, Ts...> {
  using Type = T;
};

template<be_size Index_, typename... Ts>
class TupleRecurBase_ {};

template<be_size Index_, typename T, typename... Ts>
class TupleRecurBase_<Index_, T, Ts...> :
    public TupleElement_<Index_, TypeIdentityT<T>>,
    public TupleRecurBase_<Index_ + 1, Ts...> {

public:
  TupleRecurBase_() = default;

  template<typename CT, typename... CArgs>
  TupleRecurBase_(CT&& arg, CArgs&&... args) :
      TupleElement_<Index_, TypeIdentityT<T>>(Forward<CT>(arg)),
      TupleRecurBase_<Index_ + 1, Ts...>(Forward<CArgs>(args)...) {}

  template<be_size Index>
  using ElementType = typename ExtractTypeAt<Index, T, Ts...>::Type;

  template<be_size Index>
  ElementType<Index> Get() {
    return TupleElement_<Index, ElementType<Index>>::Get();
  }

  constexpr be_size Size() const { return sizeof...(Ts) + 1; }
};

template<typename... Ts>
class Tuple : public TupleRecurBase_<0, Ts...> {
public:
  Tuple() = default;

  template<typename... CArgs>
  Tuple(CArgs&&... args) : TupleRecurBase_<0, Ts...>(Forward<CArgs>(args)...) {}
};

} // namespace BE
