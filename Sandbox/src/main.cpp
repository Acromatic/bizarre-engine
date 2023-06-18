#include "containers/Tuple.h"
#include "core/Input.h"
#include "core/Log.h"
#include "core/Window.h"
#include "math/Math.h"
#include "platform/Platform.h"
#include "utils/StringFormat.h"
#include "utils/TypeUtils.h"

#include <cstdio>

int main(int argc, char* argv[]) {
  using namespace BE;

  InitLogging(LogLevel::Trace);

  PlatformInit();
  InputInit();

  LOG_INFO("Hello, world!");
  LOG_INFO("Hello, {}", "world!");
  String fmt = "Hello, {}!";
  LOG_INFO(fmt, "world");
  LOG_INFO("Hello, {} 0x{}", "pointer", &fmt);
  LOG_INFO("Hello, hex 0x{}", 0xDEADBEEF);
  LOG_INFO("{} + {} = {}", 1, 2, 3);

  InputShutdown();
  PlatformShutdown();
  ShutdownLogging();

  return 0;
}
