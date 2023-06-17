#include "containers/Tuple.h"
#include "core/Input.h"
#include "core/Log.h"
#include "core/Window.h"
#include "platform/Platform.h"
#include "utils/TypeUtils.h"

int main(int argc, char* argv[]) {
  using namespace BE;

  InitLogging(LogLevel::Trace);

  PlatformInit();
  InputInit();

  Window* window = Window::Create("Bizarre Engine", 1280, 720, 0, 0);
  window->Show();

  b8 running = true;
  while (running) {
    running = PlatformPollEvents();
  }

  InputShutdown();
  PlatformShutdown();
  ShutdownLogging();

  return 0;
}
