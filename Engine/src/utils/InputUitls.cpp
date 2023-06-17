#include "InputUtils.h"

namespace BE {

String KeyboardKeyName(KeyboardKey key) {
  switch (key) {
    case KeyboardKey::A: return "A";
    case KeyboardKey::B: return "B";
    case KeyboardKey::C: return "C";
    case KeyboardKey::D: return "D";
    case KeyboardKey::E: return "E";
    case KeyboardKey::F: return "F";
    case KeyboardKey::G: return "G";
    case KeyboardKey::H: return "H";
    case KeyboardKey::I: return "I";
    case KeyboardKey::J: return "J";
    case KeyboardKey::K: return "K";
    case KeyboardKey::L: return "L";
    case KeyboardKey::M: return "M";
    case KeyboardKey::N: return "N";
    case KeyboardKey::O: return "O";
    case KeyboardKey::P: return "P";
    case KeyboardKey::Q: return "Q";
    case KeyboardKey::R: return "R";
    case KeyboardKey::S: return "S";
    case KeyboardKey::T: return "T";
    case KeyboardKey::U: return "U";
    case KeyboardKey::V: return "V";
    case KeyboardKey::W: return "W";
    case KeyboardKey::X: return "X";
    case KeyboardKey::Y: return "Y";
    case KeyboardKey::Z: return "Z";
    case KeyboardKey::Num0: return "Num0";
    case KeyboardKey::Num1: return "Num1";
    case KeyboardKey::Num2: return "Num2";
    case KeyboardKey::Num3: return "Num3";
    case KeyboardKey::Num4: return "Num4";
    case KeyboardKey::Num5: return "Num5";
    case KeyboardKey::Num6: return "Num6";
    case KeyboardKey::Num7: return "Num7";
    case KeyboardKey::Num8: return "Num8";
    case KeyboardKey::Num9: return "Num9";
    case KeyboardKey::Escape: return "Escape";
    case KeyboardKey::LCtrl: return "LCtrl";
    case KeyboardKey::LShift: return "LShift";
    case KeyboardKey::LAlt: return "LAlt";
    case KeyboardKey::RCtrl: return "RCtrl";
    case KeyboardKey::RShift: return "RShift";
    case KeyboardKey::RAlt: return "RAlt";
    case KeyboardKey::Space: return "Space";
    case KeyboardKey::Tab: return "Tab";
    case KeyboardKey::CapsLock: return "CapsLock";
    case KeyboardKey::Enter: return "Enter";
    case KeyboardKey::Tilde: return "Tilde";
    case KeyboardKey::Minus: return "Minus";
    case KeyboardKey::Equal: return "Equal";
    case KeyboardKey::F1: return "F1";
    case KeyboardKey::F2: return "F2";
    case KeyboardKey::F3: return "F3";
    case KeyboardKey::F4: return "F4";
    case KeyboardKey::F5: return "F5";
    case KeyboardKey::F6: return "F6";
    case KeyboardKey::F7: return "F7";
    case KeyboardKey::F8: return "F8";
    case KeyboardKey::F9: return "F9";
    case KeyboardKey::F10: return "F10";
    case KeyboardKey::F11: return "F11";
    case KeyboardKey::F12: return "F12";
    case KeyboardKey::Backspace: return "Backspace";
    case KeyboardKey::LBracket: return "LBracket";
    case KeyboardKey::RBracket: return "RBracket";
    case KeyboardKey::SemiColon: return "SemiColon";
    case KeyboardKey::Apostrophe: return "Apostrophe";
    case KeyboardKey::Backslash: return "Backslash";
    case KeyboardKey::Comma: return "Comma";
    case KeyboardKey::Period: return "Period";
    case KeyboardKey::Slash: return "Slash";
    case KeyboardKey::Left: return "Left";
    case KeyboardKey::Right: return "Right";
    case KeyboardKey::Up: return "Up";
    case KeyboardKey::Down: return "Down";
    default: return "Unknown";
  }
}

String MouseButtonName(MouseButton button) {
  switch (button) {
    case MouseButton::Left: return "MouseLeft";
    case MouseButton::Right: return "MouseRight";
    case MouseButton::Middle: return "MouseMiddle";
    case MouseButton::Button4: return "Mouse4";
    case MouseButton::Button5: return "Mouse5";
    case MouseButton::Button6: return "Mouse6";
    case MouseButton::Button7: return "Mouse7";
    case MouseButton::Button8: return "Mouse8";
    case MouseButton::Button9: return "Mouse9";
    case MouseButton::Button10: return "Mouse10";
    case MouseButton::Button11: return "Mouse11";
    case MouseButton::Button12: return "Mouse12";
    default: return "Unknown";
  }
}

} // namespace BE
