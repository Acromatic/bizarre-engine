#pragma once

#include "containers/BeString.h"
#include "containers/DynamicArray.h"
#include "containers/StringView.h"
#include "containers/Tuple.h"
#include "core/Log.h"
#include "FormattingUtils.h"
#include "math/Math.h"

namespace BE {

template<typename From_, typename To_>
struct Formatter {
  static To_ Format(From_ from) = delete;
};

template<typename From_, typename To_>
  requires Same<From_, To_>
struct Formatter<From_, To_> {
  static To_ Format(From_ from) { return from; }
};

template<typename... Args>
String Format(const String& format, Args... args) {
  if (sizeof...(Args) == 0) {
    return format;
  }

  DynamicArray<String> strings{sizeof...(Args)};
  (strings.PushBack(Formatter<Args, String>::Format(args)), ...);

  String result;

  be_size pos{0};
  for (be_size i{0}; i < strings.Size(); ++i) {
    be_size openBracket = format.Find(pos, '{');
    if (openBracket == String::NPos) {
      result += format.SubString(pos, format.Size() - pos);
      break;
    }

    be_size closeBracket = format.Find(openBracket, '}');
    if (closeBracket == String::NPos) {
      result += format.SubString(pos, format.Size() - pos);
      break;
    }

    if (openBracket != pos) {
      result += format.SubString(pos, openBracket - pos);
    }
    result += strings[i];
    pos     = closeBracket + 1;
  }
  if (pos < format.Size()) {
    result += format.SubString(pos, format.Size() - pos);
  }

  return result;
}

template<>
struct Formatter<const char*, String> {
  static String Format(const char* from) { return String(from); }
};

template<UnsignedInteger T_>
struct Formatter<T_, String> {
  static String Format(T_ from) {
    using T = typename RemoveConst<T_>::Type;

    T abs      = from;
    u32 digits = abs > 0 ? (u32)Math::Log10((f32)abs) + 1 : 1;

    String result(digits);

    for (u32 i = 0; i < digits; ++i) {
      result[digits - i - 1]  = '0' + (abs % 10);
      abs                    /= 10;
    }

    result.Resize(digits);
    return result;
  }
};

template<Integral T_>
struct Formatter<T_, String> {
  static String Format(T_ from) {
    using T = typename RemoveConst<T_>::Type;

    b8 negative = from < 0;
    T abs       = negative ? -from : from;
    u32 digits  = abs > 0 ? (u32)Math::Log10((f32)abs) + 1 : 1;

    String result(digits + negative);

    if (negative) {
      result[0] = '-';
    }

    for (u32 i = 0; i < digits; ++i) {
      result[digits - i - 1 + negative]  = '0' + (abs % 10);
      abs                               /= 10;
    }

    result.Resize(digits + negative);
    return result;
  }
};

template<FloatingPoint T_>
struct Formatter<T_, String> {
  static String Format(T_ from) { return FloatToString(from); }
};

template<Pointer T_>
struct Formatter<T_, String> {
  static String Format(T_ from) { return ToHex(from); }
};

} // namespace BE
