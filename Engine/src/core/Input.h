#pragma once

#include "Defines.h"
#include "KeyCodes.h"

namespace BE {

b8 InputInit();

/**
 * Update Input state for the key
 * @returns true if key state was updated
 */
b8 InputProcessKey(KeyboardKey key, b8 isDown);

/**
 * Update intut state for the button
 * @returns true if the button state was updated
 */
b8 InputProcessButton(MouseButton button, b8 isDown);

b8 InputUpdate();

void InputShutdown();

BeFlags GetKeyboardModifiers();
b8 AreModifiersApplied(BeFlags modifiers);

b8 IsKeyDown(KeyboardKey key);
b8 WasKeyDown(KeyboardKey key);
b8 WasKeyUp(KeyboardKey key);

b8 IsMouseButtonDown(MouseButton button);
b8 WasMouseButtonDown(MouseButton button);
b8 WasMouseButtonUp(MouseButton button);

} // namespace BE
