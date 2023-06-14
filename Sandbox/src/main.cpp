#include "core/log.h"
#include "core/window.h"
#include "platform/platform.h"

int main(int argc, char *argv[]) {
  BE::InitLogging(BE::LogLevel::Trace);

  BE::PlatformInit();
  BE::Window *window = BE::Window::Create("Hello World", 800, 600, 500, 50);
  BE::Window *child  = window->CreateChild("", 300, 300, 100, 20);
  window->Show();
  child->Show();

  bool result = true;
  while (result) {
    result = BE::PlatformPollEvents();
  }

  BE::PlatformShutdown();
  BE::ShutdownLogging();

  return 0;
}
