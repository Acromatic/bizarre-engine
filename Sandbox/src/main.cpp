#include "core/log.h"
#include "core/window.h"
#include "platform/platform.h"

int main(int argc, char *argv[]) {
  BE::InitLogging(BE::LogLevel::Trace);

  BE::PlatformInit();
  BE::Window *splash = BE::Window::Create("Splash", 1000, 300, 100, 100, BE::WindowType::Splash);
  splash->Show();
  BE::PlatformSleep(1000);
  splash->Close();

  // Creates a mess of windows, and almost all of theme does not give a damn about the position
  BE::Window *window      = BE::Window::Create("Hello World", 1270, 720, 500, 50);
  BE::Window *normalChild = window->CreateChild("Normal Child", 100, 100, 500, 500);
  BE::Window *dialogChild =
      window->CreateChild("Dialog Child", 100, 100, 1000, 1000, BE::WindowType::Dialog);
  BE::Window *menuChild =
      window->CreateChild("Menu Child", 100, 100, 120, 120, BE::WindowType::Menu);
  BE::Window *toolbarChild =
      window->CreateChild("Toolbar Child", 100, 100, 300, 300, BE::WindowType::Toolbar);
  BE::Window *utilityChild =
      window->CreateChild("Utility Child", 100, 100, 10, 120, BE::WindowType::Utility);

  window->Show();
  normalChild->Show();
  dialogChild->Show();
  menuChild->Show();
  toolbarChild->Show();
  utilityChild->Show();

  bool result = true;
  while (result) {
    result = BE::PlatformPollEvents();
  }

  BE::PlatformShutdown();
  BE::ShutdownLogging();

  return 0;
}
