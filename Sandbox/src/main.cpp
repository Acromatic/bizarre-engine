#include "core/Log.h"
#include "core/Window.h"
#include "platform/Platform.h"

int main(int argc, char *argv[]) {
  BE::InitLogging(BE::LogLevel::Trace);

  BE::PlatformInit();
  BE::Window *splash = BE::Window::Create("Splash", 1000, 300, 100, 100, BE::WindowType::Splash);
  splash->Show();
  BE::PlatformSleep(1000);
  splash->Close();

  // Creates a mess of windows, and almost all of theme does not give a damn about the position
  BE::Window *window = BE::Window::Create(
      "Hello World", 1270, 720, 250, 100, BE::WindowType::MainWindow, BE::WindowMode::Windowed
  );

  window->Show(true);

  BE::PlatformSleep(1000);
  window->SetWindowMode(BE::WindowMode::Fullscreen);

  bool result = true;
  while (result) {
    result = BE::PlatformPollEvents();
  }

  BE::PlatformShutdown();
  BE::ShutdownLogging();

  return 0;
}
