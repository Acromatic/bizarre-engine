#pragma once

#include "core/Defines.h"
#include "core/Window.h"

#include <xcb/xcb.h>

namespace BE {

xcb_atom_t RetrieveXcbAtom(xcb_connection_t* connection, const char* name, b8 ifOnlyExists = false);
xcb_atom_t WindowTypeToXcbAtom(xcb_connection_t* connection, WindowType type);
xcb_atom_t WindowStateToXcbAtom(xcb_connection_t* connection, WindowState state);

} // namespace BE
