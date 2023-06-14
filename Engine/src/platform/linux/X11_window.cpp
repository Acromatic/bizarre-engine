#include "X11_window.h"

#include "core/log.h"
#include "platform/platform.h"

namespace BE {
X11Window::X11Window(const char* title, u32 width, u32 height, i32 x, i32 y) :
    m_Title(title),
    m_Width(width),
    m_Height(height) {
  m_Context = new X11WindowContext{0};
  PlatformCreateNativeWindow(title, width, height, x, y, m_Context);
}

X11Window::X11Window(
    const char* title, u32 width, u32 height, i32 x, i32 y, const X11Window& parent
) :
    m_Title(title),
    m_Width(width),
    m_Height(height) {
  m_Context = new X11WindowContext{0};
  PlatformCreateNativeWindow(title, width, height, x, y, m_Context, &parent);
}

X11Window::~X11Window() {
  if (m_Context) {
    xcb_destroy_window(m_Context->connection, m_Context->window);
    delete m_Context;
  }
}

void* X11Window::NativeHandle() const {
  if (m_Context) {
    return &m_Context->window;
  }

  return nullptr;
}

Window* X11Window::CreateChild(const char* title, u32 width, u32 height, i32 x, i32 y) {
  return new X11Window(title, width, height, x, y, *this);
}

void X11Window::SetTitle(const String& title) {}

void X11Window::SetWidth(u32 width) {
  m_Width = width;
}

void X11Window::SetHeight(u32 height) {
  m_Height = height;
}

b8 X11Window::Show() {
  xcb_map_window(m_Context->connection, m_Context->window);
  xcb_flush(m_Context->connection);
  return true;
}

void X11Window::Close() {}

b8 X11Window::ShouldClose() const {
  return false;
}

b8 X11Window::PollEvents() {
  return true;
}

} // namespace BE
