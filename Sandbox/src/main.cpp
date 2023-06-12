#include <BizarreEngine.h>

int main() {
  BE::InitLogging(BE::LogLevel::Trace);
  LOG_TRACE("Hello, World!");
  LOG_TRACE("Trace Message: %s", "Hello, World!");
  LOG_DEBUG("Hello, World!");
  LOG_DEBUG("Debug Message: %s", "Hello, World!");
  LOG_INFO("Hello, World!");
  LOG_INFO("Info Message: %s", "Hello, World!");
  LOG_WARN("Hello, World!");
  LOG_WARN("Warn Message: %s", "Hello, World!");
  LOG_ERROR("Hello, World!");
  LOG_ERROR("Error Message: %s", "Hello, World!");
  LOG_FATAL("Hello, World!");
  LOG_FATAL("Fatal Message: %s", "Hello, World!");

  BE_ASSERT_MSG(false, "bad assertion");
  BE::ShutdownLogging();
  return 0;
}
