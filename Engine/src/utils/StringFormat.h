#pragma once

#include <containers/BeString.h>
#include <format>

namespace BE {

template<typename... Args>
class FormatString {};

template<typename... Args>
String Format(std::format_string<Args...> format, Args &&...args) {
  return String(std::format(format, std::forward<Args>(args)...).c_str());
}
} // namespace BE
