#include "x11_utils.h"

#include <cstdlib>
#include <cstring>

namespace BE {
xcb_atom_t RetrieveXcbAtom(xcb_connection_t* connection, const char* name, b8 ifOnlyExists) {
  xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection, ifOnlyExists, strlen(name), name);
  xcb_intern_atom_reply_t* reply  = xcb_intern_atom_reply(connection, cookie, nullptr);

  if (!reply) {
    return XCB_ATOM_NONE;
  }

  xcb_atom_t atom = reply->atom;
  free(reply);

  return atom;
}

xcb_atom_t WindowTypeToXcbAtom(xcb_connection_t* connection, WindowType type) {
  switch (type) {
    case WindowType::MainWindow:
    case WindowType::NormalWindow:
      return RetrieveXcbAtom(connection, "_NET_WM_WINDOW_TYPE_NORMAL", false);
    case WindowType::Menu: return RetrieveXcbAtom(connection, "_NET_WM_WINDOW_TYPE_MENU", true);
    case WindowType::Popup:
    case WindowType::Toolbar:
      return RetrieveXcbAtom(connection, "_NET_WM_WINDOW_TYPE_TOOLBAR", true);
    case WindowType::Dialog: return RetrieveXcbAtom(connection, "_NET_WM_WINDOW_TYPE_DIALOG", true);
    case WindowType::Splash: return RetrieveXcbAtom(connection, "_NET_WM_WINDOW_TYPE_SPLASH", true);
    case WindowType::Utility:
      return RetrieveXcbAtom(connection, "_NET_WM_WINDOW_TYPE_UTILITY", true);
    default: return XCB_ATOM_NONE;
  }
}

} // namespace BE
