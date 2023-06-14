#include "window.h"

#if defined(BE_PLATFORM_LINUX)
  #include "platform/linux/X11_window.h"
#endif

namespace BE {
Window *Window::Create(const char *title, u32 width, u32 height, i32 x, i32 y) {
#if defined(BE_PLATFORM_LINUX)
  return new X11Window(title, width, height, x, y);
#elif defined(BE_PLATFORM_WINDOWS)
  return nullptr;
#elif defined(BE_PLATFORM_MACOS)
  return nullptr;
#endif
}
} // namespace BE
