#pragma once

#include "containers/be_string.h"
#include "defines.h"

namespace BE {

class Window {
public:
  virtual ~Window() = default;

  virtual Window* CreateChild(const char* title, u32 width, u32 height, i32 x = 0, i32 y = 0) = 0;

  virtual void* NativeHandle() const  = 0;
  virtual u32 Width() const           = 0;
  virtual u32 Height() const          = 0;
  virtual const String& Title() const = 0;

  virtual void SetTitle(const String& title) = 0;
  virtual void SetWidth(u32 width)           = 0;
  virtual void SetHeight(u32 height)         = 0;

  virtual b8 Show()    = 0;
  virtual void Close() = 0;

  virtual b8 ShouldClose() const = 0;
  virtual b8 PollEvents()        = 0;

  static Window* Create(const char* title, u32 width, u32 height, i32 x, i32 y);
};
} // namespace BE
