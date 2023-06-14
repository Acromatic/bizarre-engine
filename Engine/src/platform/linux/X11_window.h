#pragma once

#include "core/defines.h"

#include <xcb/xcb.h>

#if defined(BE_PLATFORM_LINUX)

  #include "core/window.h"

namespace BE {

struct X11WindowContext {
  xcb_connection_t* connection;
  xcb_screen_t* screen;
  xcb_window_t window;
};

class X11Window : public Window {
public:
  X11Window(const char* title, u32 width, u32 height);
  virtual ~X11Window();

  virtual void* NativeHandle() const override;

  virtual u32 Width() const override { return m_Width; }

  virtual u32 Height() const override { return m_Height; }

  virtual const String& Title() const override { return m_Title; }

  virtual void SetTitle(const String& title) override;

  virtual void SetWidth(u32 width) override;
  virtual void SetHeight(u32 height) override;

  virtual b8 Show() override;
  virtual void Close() override;

  virtual b8 ShouldClose() const override;
  virtual b8 PollEvents() override;

private:
  String m_Title;
  u32 m_Width, m_Height;

  X11WindowContext* m_Context;
};

} // namespace BE

#endif
