#include "StringUtils.h"

namespace BE {
be_size StrLen(const char* str) {
  be_size len = 0;
  while (*str++) {
    ++len;
  }
  return len;
}
} // namespace BE
