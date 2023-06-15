#pragma once

#include "containers/be_string.h"
#include "defines.h"
#include "math/Vector.h"

namespace BE {

enum class WindowType {
  MainWindow,
  NormalWindow,
  Splash,
  Dialog,
  Toolbar,
  Popup,
  Menu,
  Utility,
  EnumCount
};

enum class WindowMode {
  Windowed,
  Fullscreen,
  BorderlessFullscreen,
  EnumCount
};

enum class WindowState {
  Maximized,
  Minimized,
  Normal,
  EnumCount
};

class Window {
public:
  virtual ~Window() = default;

  virtual Window* CreateChild(
      const char* title,
      u32 width,
      u32 height,
      i32 x             = 0,
      i32 y             = 0,
      WindowType type   = WindowType::NormalWindow,
      WindowMode mode   = WindowMode::Windowed,
      WindowState state = WindowState::Normal
  ) = 0;

  virtual void* NativeHandle() const = 0;

  virtual u32 Width() const           = 0;
  virtual u32 Height() const          = 0;
  virtual const String& Title() const = 0;

  virtual void SetTitle(const String& title) = 0;
  virtual void SetWidth(u32 width)           = 0;
  virtual void SetHeight(u32 height)         = 0;

  virtual Vec2i Position() const         = 0;
  virtual void SetPosition(i32 x, i32 y) = 0;

  virtual void SetPosition(const Vec2i& pos) { SetPosition(pos.x, pos.y); }

  virtual b8 Show(b8 forcePosition = false) = 0;
  virtual void Close()                      = 0;

  virtual void SetWindowMode(WindowMode mode)    = 0;
  virtual void SetWindowState(WindowState state) = 0;

  virtual b8 ShouldClose() const = 0;
  virtual b8 PollEvents()        = 0;

  static Window* Create(
      const char* title,
      u32 width,
      u32 height,
      i32 x,
      i32 y,
      WindowType type   = WindowType::MainWindow,
      WindowMode mode   = WindowMode::Windowed,
      WindowState state = WindowState::Normal
  );
};
} // namespace BE
