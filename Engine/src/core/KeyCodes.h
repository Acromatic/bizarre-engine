#pragma once

#include "core/Defines.h"

namespace BE {
enum class KeyboardKey : u8 {
  A = 0x26,
  B = 0x38,
  C = 0x36,
  D = 0x28,
  E = 0x1A,
  F = 0x29,
  G = 0x2A,
  H = 0x2B,
  I = 0x1F,
  J = 0x2C,
  K = 0x2D,
  L = 0x2E,
  M = 0x3A,
  N = 0x39,
  O = 0x20,
  P = 0x21,
  Q = 0x18,
  R = 0x1B,
  S = 0x27,
  T = 0x1C,
  U = 0x1E,
  V = 0x37,
  W = 0x19,
  X = 0x35,
  Y = 0x1D,
  Z = 0x34,

  Escape   = 0x09,
  Enter    = 0x24,
  Space    = 0x41,
  RCtrl    = 0x69,
  LCtrl    = 0x25,
  RShift   = 0x3E,
  LShift   = 0x32,
  RAlt     = 0x6C,
  LAlt     = 0x40,
  CapsLock = 0x42,
  Tab      = 0x17,

  Tilde = 0x31,
  Num1  = 0x0A,
  Num2  = 0x0B,
  Num3  = 0x0C,
  Num4  = 0x0D,
  Num5  = 0x0E,
  Num6  = 0x0F,
  Num7  = 0x10,
  Num8  = 0x11,
  Num9  = 0x12,
  Num0  = 0x13,

  Minus = 0x14,
  Equal = 0x15,

  Backspace = 0x16,

  LBracket   = 0x22,
  RBracket   = 0x23,
  Backslash  = 0x33,
  SemiColon  = 0x2F,
  Apostrophe = 0x30,
  Comma      = 0x3b,
  Period     = 0x3c,
  Slash      = 0x3d,

  Right = 0x72,
  Left  = 0x71,
  Up    = 0x6f,
  Down  = 0x74,

  F1  = 0x43,
  F2  = 0x44,
  F3  = 0x45,
  F4  = 0x46,
  F5  = 0x47,
  F6  = 0x48,
  F7  = 0x49,
  F8  = 0x4a,
  F9  = 0x4b,
  F10 = 0x4c,
  F11 = 0x5f,
  F12 = 0x60,

  MaxKeys = 0xFF
};

enum class KeyboardModifierBits : BeFlags {
  LShift = BIT(0),
  RShift = BIT(1),
  LCtrl  = BIT(2),
  RCtrl  = BIT(3),
  LAlt   = BIT(4),
  RAlt   = BIT(5),
  Shift  = BIT(6),
  Ctrl   = BIT(7),
  Alt    = BIT(8)
};

enum class MouseButton : u8 {
  Button1  = 0x01,
  Button2  = 0x02,
  Button3  = 0x03,
  Button4  = 0x04,
  Button5  = 0x05,
  Button6  = 0x06,
  Button7  = 0x07,
  Button8  = 0x08,
  Button9  = 0x09,
  Button10 = 0x0A,
  Button11 = 0x0B,
  Button12 = 0x0C,

  Left   = Button1,
  Middle = Button2,
  Right  = Button3,

  MaxButtons = 0x0F
};

} // namespace BE
