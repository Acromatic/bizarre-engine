#pragma once

#include "core/Defines.h"

namespace BE {
void ReportFailedAssert(
    const char* expression, const char* file, int line, const char* msg = nullptr
);
}

#if defined(DEBUG)
  #define BE_ASSERT(expr)                                  \
    if (!(expr)) {                                         \
      ::BE::ReportFailedAssert(#expr, __FILE__, __LINE__); \
      BE_DEBUG_BREAK();                                    \
    }
  #define BE_ASSERT_MSG(expr, msg)                              \
    if (!(expr)) {                                              \
      ::BE::ReportFailedAssert(#expr, __FILE__, __LINE__, msg); \
      BE_DEBUG_BREAK();                                         \
    }
#else
  #define BE_ASSERT(expr)
  #define BE_ASSERT_MSG(expr, msg)
#endif

#define BE_RELEASE_ASSERT(expr)                          \
  if (!(expr)) {                                         \
    ::BE::ReportFailedAssert(#expr, __FILE__, __LINE__); \
    BE_DEBUG_BREAK();                                    \
  }

#define BE_RELEASE_ASSERT_MSG(expr, msg)                      \
  if (!(expr)) {                                              \
    ::BE::ReportFailedAssert(#expr, __FILE__, __LINE__, msg); \
    BE_DEBUG_BREAK();                                         \
  }
