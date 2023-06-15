#include "Window.h"

#include "core/BeAssert.h"

#if defined(BE_PLATFORM_LINUX)
  #include "platform/linux/X11Window.h"
#endif

namespace BE {
Window *Window::Create(
    const char *title,
    u32 width,
    u32 height,
    i32 x,
    i32 y,
    WindowType type,
    WindowMode mode,
    WindowState state
) {
  BE_ASSERT_MSG(
      type == WindowType::MainWindow || type == WindowType::Splash, "Window type not supported"
  );
#if defined(BE_PLATFORM_LINUX)
  return new X11Window(title, width, height, x, y, type, mode, state);
#elif defined(BE_PLATFORM_WINDOWS)
  return nullptr;
#elif defined(BE_PLATFORM_MACOS)
  return nullptr;
#endif
}
} // namespace BE
