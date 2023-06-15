#include "X11_window.h"

#include "core/log.h"
#include "platform/platform.h"

namespace BE {
X11Window::X11Window(const char* title, u32 width, u32 height, i32 x, i32 y, WindowType type) :
    m_Title(title),
    m_Width(width),
    m_Height(height),
    m_Position{x, y} {
  m_Context = new X11WindowContext{0};
  PlatformCreateNativeWindow(title, width, height, x, y, type, m_Context);
}

X11Window::X11Window(
    const char* title, u32 width, u32 height, i32 x, i32 y, WindowType type, const X11Window& parent
) :
    m_Title(title),
    m_Width(width),
    m_Height(height),
    m_Position{x, y} {
  m_Context = new X11WindowContext{0};
  PlatformCreateNativeWindow(title, width, height, x, y, type, m_Context, &parent);
}

X11Window::~X11Window() {
  Close();
}

void* X11Window::NativeHandle() const {
  if (m_Context) {
    return &m_Context->window;
  }

  return nullptr;
}

Window*
X11Window::CreateChild(const char* title, u32 width, u32 height, i32 x, i32 y, WindowType type) {
  return new X11Window(title, width, height, x, y, type, *this);
}

void X11Window::SetTitle(const String& title) {}

void X11Window::SetWidth(u32 width) {
  m_Width = width;
}

void X11Window::SetHeight(u32 height) {
  m_Height = height;
}

void X11Window::SetPosition(i32 x, i32 y) {
  m_Position = {x, y};
  xcb_configure_window(
      m_Context->connection,
      m_Context->window,
      XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,
      &m_Position
  );
}

b8 X11Window::Show(b8 forcePosition) {
  xcb_map_window(m_Context->connection, m_Context->window);
  if (forcePosition)
    SetPosition(m_Position.x, m_Position.y);
  xcb_flush(m_Context->connection);
  return true;
}

void X11Window::Close() {
  if (m_Context) {
    xcb_destroy_window(m_Context->connection, m_Context->window);
    delete m_Context;
    m_Context = nullptr;
  }
}

b8 X11Window::ShouldClose() const {
  return false;
}

b8 X11Window::PollEvents() {
  return true;
}

} // namespace BE
