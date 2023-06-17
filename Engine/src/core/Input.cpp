#include "Input.h"

#include "core/Log.h"
#include "math/Limits.h"
#include "utils/InputUtils.h"
#include "utils/StringFormat.h"

#include <cstring>

namespace BE {

static b8 s_KeyboardState[(be_size)KeyboardKey::MaxKeys];
static b8 s_KeyboardPreviousState[(be_size)KeyboardKey::MaxKeys];

static b8 s_MouseState[(be_size)MouseButton::MaxButtons];
static b8 s_MousePreviousState[(be_size)MouseButton::MaxButtons];

static BeFlags s_KeyboardModifiers{0};

b8 InputInit() {
  for (be_size i{0}; i < (be_size)KeyboardKey::MaxKeys; ++i) {
    s_KeyboardState[i]         = false;
    s_KeyboardPreviousState[i] = false;
  }
  for (be_size i{0}; i < (be_size)MouseButton::MaxButtons; ++i) {
    s_MouseState[i]         = false;
    s_MousePreviousState[i] = false;
  }

  return true;
}

String ModifiersToString() {
  return Format(
      "Shift: {}, Ctrl: {}, Alt: {}",
      s_KeyboardModifiers & (BeFlags)KeyboardModifierBits::Shift ? "yes" : "no",
      s_KeyboardModifiers & (BeFlags)KeyboardModifierBits::Ctrl ? "yes" : "no",
      s_KeyboardModifiers & (BeFlags)KeyboardModifierBits::Alt ? "yes" : "no"
  );
}

b8 InputProcessKey(KeyboardKey key, b8 isDown) {
  if ((be_size)key >= (be_size)KeyboardKey::MaxKeys) {
    LOG_ERROR("Invalid key %s", key);
    return false;
  }

  if (s_KeyboardState[(be_size)key] == isDown)
    return false;

  s_KeyboardState[(be_size)key] = isDown;
  LOG_TRACE(
      "Key %s (0x%x) is %s, modifiers applied: %s",
      KeyboardKeyName(key).Data(),
      key,
      isDown ? "down" : "up",
      ModifiersToString().Data()
  );

  switch (key) {
    case KeyboardKey::LShift:
      if (isDown) {
        s_KeyboardModifiers |=
            (BeFlags)KeyboardModifierBits::LShift | (BeFlags)KeyboardModifierBits::Shift;
      } else {
        s_KeyboardModifiers &=
            ~(BeFlags)KeyboardModifierBits::LShift
            & (IsKeyDown(KeyboardKey::RShift) ? Limits<BeFlags>::Max()
                                              : ~(BeFlags)KeyboardModifierBits::Shift);
      }
      break;
    case KeyboardKey::RShift:
      if (isDown) {
        s_KeyboardModifiers |=
            (BeFlags)KeyboardModifierBits::RShift | (BeFlags)KeyboardModifierBits::Shift;
      } else {
        s_KeyboardModifiers &=
            ~(BeFlags)KeyboardModifierBits::RShift
            & (IsKeyDown(KeyboardKey::LShift) ? Limits<BeFlags>::Max()
                                              : ~(BeFlags)KeyboardModifierBits::Shift);
      }
      break;
    case KeyboardKey::LCtrl:
      if (isDown) {
        s_KeyboardModifiers |=
            (BeFlags)KeyboardModifierBits::LCtrl | (BeFlags)KeyboardModifierBits::Ctrl;
      } else {
        s_KeyboardModifiers &=
            ~(BeFlags)KeyboardModifierBits::LCtrl
            & (IsKeyDown(KeyboardKey::RCtrl) ? Limits<BeFlags>::Max()
                                             : ~(BeFlags)KeyboardModifierBits::Ctrl);
      }
      break;

    case KeyboardKey::RCtrl:
      if (isDown) {
        s_KeyboardModifiers |=
            (BeFlags)KeyboardModifierBits::RCtrl | (BeFlags)KeyboardModifierBits::Ctrl;
      } else {
        s_KeyboardModifiers &=
            ~(BeFlags)KeyboardModifierBits::RCtrl
            & (IsKeyDown(KeyboardKey::LCtrl) ? Limits<BeFlags>::Max()
                                             : ~(BeFlags)KeyboardModifierBits::Ctrl);
      }
      break;
    case KeyboardKey::LAlt:
      if (isDown) {
        s_KeyboardModifiers |=
            (BeFlags)KeyboardModifierBits::LAlt | (BeFlags)KeyboardModifierBits::Alt;
      } else {
        s_KeyboardModifiers &=
            ~(BeFlags)KeyboardModifierBits::LAlt
            & (IsKeyDown(KeyboardKey::RAlt) ? Limits<BeFlags>::Max()
                                            : ~(BeFlags)KeyboardModifierBits::Alt);
      }
      break;
    case KeyboardKey::RAlt:
      if (isDown) {
        s_KeyboardModifiers |=
            (BeFlags)KeyboardModifierBits::RAlt | (BeFlags)KeyboardModifierBits::Alt;
      } else {
        s_KeyboardModifiers &=
            ~(BeFlags)KeyboardModifierBits::RAlt
            & (IsKeyDown(KeyboardKey::LAlt) ? Limits<BeFlags>::Max()
                                            : ~(BeFlags)KeyboardModifierBits::Alt);
      }
      break;
    default: break;
  }

  return true;
}

BeFlags GetKeyboardModifiers() {
  return s_KeyboardModifiers;
}

b8 AreModifiersApplied(BeFlags modifiers) {
  return (s_KeyboardModifiers & modifiers) == modifiers;
}

b8 InputProcessButton(MouseButton button, b8 isDown) {
  if ((be_size)button >= (be_size)MouseButton::MaxButtons) {
    LOG_ERROR("Invalid mouse button %s", button);
    return false;
  }

  if (s_MouseState[(be_size)button] == isDown)
    return false;

  s_MouseState[(be_size)button] = isDown;
  LOG_TRACE(
      "Mouse button %s (0x%x) is %s", MouseButtonName(button).Data(), button, isDown ? "down" : "up"
  );

  return true;
}

b8 InputUpdate() {
  memcpy(s_KeyboardPreviousState, s_KeyboardState, sizeof(s_KeyboardState));
  memcpy(s_MousePreviousState, s_MouseState, sizeof(s_MouseState));

  return true;
}

void InputShutdown() {}

b8 IsKeyDown(KeyboardKey key) {
  return s_KeyboardState[(be_size)key];
}

b8 WasKeyDown(KeyboardKey key) {
  return s_KeyboardPreviousState[(be_size)key];
}

b8 IsMouseButtonDown(MouseButton button) {
  return s_MouseState[(be_size)button];
}

b8 WasMouseButtonDown(MouseButton button) {
  return s_MousePreviousState[(be_size)button];
}

} // namespace BE
