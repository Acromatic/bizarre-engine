#include "core/Defines.h"

#include <cstdlib>
#include <cstring>

#if defined(BE_PLATFORM_LINUX)
  #include "containers/DynamicArray.h"
  #include "core/Log.h"
  #include "platform/linux/X11Utils.h"
  #include "platform/Platform.h"
  #include "X11Window.h"

  #include <unistd.h>
  #include <xcb/xcb.h>
  #include <xcb/xcb_util.h>

namespace BE {
struct PlatformState {
  b8 init;

  xcb_connection_t* connection;
  xcb_screen_t* screen;
  xcb_atom_t wmDeleteWindow;
  xcb_atom_t wmProtocols;
};

PlatformState s_State{0};

// internal functions

static inline xcb_atom_t WindowTypeToXcbAtom_internal(WindowType type) {
  switch (type) {
    case WindowType::MainWindow:
    case WindowType::NormalWindow:
      return RetrieveXcbAtom(s_State.connection, "_NET_WM_WINDOW_TYPE_NORMAL", false);
    case WindowType::Menu:
      return RetrieveXcbAtom(s_State.connection, "_NET_WM_WINDOW_TYPE_MENU", true);
    case WindowType::Popup:
    case WindowType::Toolbar:
      return RetrieveXcbAtom(s_State.connection, "_NET_WM_WINDOW_TYPE_TOOLBAR", true);
    case WindowType::Dialog:
      return RetrieveXcbAtom(s_State.connection, "_NET_WM_WINDOW_TYPE_DIALOG", true);
    case WindowType::Splash:
      return RetrieveXcbAtom(s_State.connection, "_NET_WM_WINDOW_TYPE_SPLASH", true);
    case WindowType::Utility:
      return RetrieveXcbAtom(s_State.connection, "_NET_WM_WINDOW_TYPE_UTILITY", true);
    default: return XCB_ATOM_NONE;
  }
}

// Exposed Platfrom API

b8 PlatformInit() {
  if (s_State.init) {
    return true;
  }

  i32 screenNum;
  s_State.connection = xcb_connect(nullptr, &screenNum);

  if (xcb_connection_has_error(s_State.connection)) {
    LOG_ERROR("Failed to connect to X server");
    return false;
  }

  const xcb_setup_t* setup   = xcb_get_setup(s_State.connection);
  xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);

  for (i32 i{0}; i < screenNum; ++i) {
    xcb_screen_next(&iter);
  }

  s_State.screen = iter.data;

  LOG_INFO("Screen information: %d", s_State.screen->root);
  LOG_INFO("\twidth: %d", s_State.screen->width_in_pixels);
  LOG_INFO("\theight: %d", s_State.screen->height_in_pixels);
  LOG_INFO("\twhite pixel: %d", s_State.screen->white_pixel);
  LOG_INFO("\tblack pixel: %d", s_State.screen->black_pixel);

  s_State.init = true;
  return true;
}

void PlatformShutdown() {
  if (!s_State.init) {
    return;
  }

  xcb_disconnect(s_State.connection);

  s_State.init = false;
}

b8 PlatformCreateNativeWindow(
    const char* title,
    u32 width,
    u32 height,
    i32 x,
    i32 y,
    WindowType type,
    WindowMode mode,
    WindowState state,
    void* windowDataHandle,
    const Window* parent
) {
  BE_ASSERT_MSG(s_State.init, "Platform not initialized");
  BE_ASSERT_MSG(windowDataHandle, "Window data handle is null");

  if (type == WindowType::MainWindow || type == WindowType::Splash) {
    if (parent) {
      LOG_ERROR("Main window or splash cannot have a parent");
      return false;
    }
  } else {
    if (!parent) {
      LOG_ERROR("Child window must have a parent");
      return false;
    }
    if (mode == WindowMode::Fullscreen || mode == WindowMode::BorderlessFullscreen) {
      LOG_ERROR("Child window cannot be fullscreen");
      return false;
    }
  }

  xcb_window_t windowId = xcb_generate_id(s_State.connection);
  u32 valueMask         = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  u32 valueList[2]{};
  valueList[0] = s_State.screen->black_pixel;

  valueList[1] = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE
                 | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE
                 | XCB_EVENT_MASK_POINTER_MOTION | XCB_EVENT_MASK_STRUCTURE_NOTIFY;

  xcb_create_window(
      s_State.connection,
      XCB_COPY_FROM_PARENT,
      windowId,
      s_State.screen->root,
      (i16)x,
      (i16)y,
      width,
      height,
      0,
      XCB_WINDOW_CLASS_INPUT_OUTPUT,
      s_State.screen->root_visual,
      valueMask,
      &valueList
  );

  xcb_change_property(
      s_State.connection,
      XCB_PROP_MODE_REPLACE,
      windowId,
      XCB_ATOM_WM_ICON_NAME,
      XCB_ATOM_STRING,
      8,
      strlen(title),
      title
  );

  if (type != WindowType::MainWindow && type != WindowType::Splash) {
    xcb_window_t transientFor = *(xcb_window_t*)parent->NativeHandle();

    xcb_change_property(
        s_State.connection,
        XCB_PROP_MODE_REPLACE,
        windowId,
        XCB_ATOM_WM_TRANSIENT_FOR,
        XCB_ATOM_WINDOW,
        32,
        1,
        &transientFor
    );

  } else {
    i32 titleLen  = strlen(title);
    char* wmClass = new char[2 * titleLen + 1]{0};
    for (u32 i{0}; i < strlen(title); ++i) {
      wmClass[i]                = title[i];
      wmClass[i + titleLen + 1] = title[i];
    }

    xcb_change_property(
        s_State.connection,
        XCB_PROP_MODE_REPLACE,
        windowId,
        XCB_ATOM_WM_CLASS,
        XCB_ATOM_STRING,
        8,
        2 * strlen(title) + 1,
        wmClass
    );
  }

  xcb_atom_t netWmWindowType = RetrieveXcbAtom(s_State.connection, "_NET_WM_WINDOW_TYPE", false);
  xcb_atom_t windowType      = WindowTypeToXcbAtom_internal(type);

  xcb_change_property(
      s_State.connection,
      XCB_PROP_MODE_REPLACE,
      windowId,
      netWmWindowType,
      XCB_ATOM_ATOM,
      32,
      1,
      &windowType
  );

  xcb_atom_t wmStateAtom = RetrieveXcbAtom(s_State.connection, "_NET_WM_STATE", false);

  switch (mode) {
    case WindowMode::Windowed: {
      xcb_atom_t windowState = RetrieveXcbAtom(s_State.connection, "_NET_WM_STATE_NORMAL", false);
      xcb_change_property(
          s_State.connection,
          XCB_PROP_MODE_REPLACE,
          windowId,
          wmStateAtom,
          XCB_ATOM_ATOM,
          32,
          1,
          &windowState
      );
    } break;

      // There is no destinction at the moment. I'm working on it, I promise.
    case WindowMode::BorderlessFullscreen:
    case WindowMode::Fullscreen: {
      xcb_atom_t windowState =
          RetrieveXcbAtom(s_State.connection, "_NET_WM_STATE_FULLSCREEN", false);
      xcb_change_property(
          s_State.connection,
          XCB_PROP_MODE_REPLACE,
          windowId,
          wmStateAtom,
          XCB_ATOM_ATOM,
          32,
          1,
          &windowState
      );
    } break;

    default: LOG_ERROR("Unknown window mode");
  }

  if (mode == WindowMode::Windowed) {
    switch (state) {
      case WindowState::Maximized: {
        xcb_atom_t maxV =
            RetrieveXcbAtom(s_State.connection, "_NET_WM_STATE_MAXIMIZED_VERT", false);
        xcb_atom_t maxH =
            RetrieveXcbAtom(s_State.connection, "_NET_WM_STATE_MAXIMIZED_HORZ", false);

        xcb_atom_t maximized[2]{maxV, maxH};
        xcb_change_property(
            s_State.connection,
            XCB_PROP_MODE_APPEND,
            windowId,
            wmStateAtom,
            XCB_ATOM_ATOM,
            32,
            2,
            maximized
        );
      } break;
      case WindowState::Minimized: {
        xcb_atom_t hidden = RetrieveXcbAtom(s_State.connection, "_NET_WM_STATE_HIDDEN", false);
        xcb_change_property(
            s_State.connection,
            XCB_PROP_MODE_APPEND,
            windowId,
            wmStateAtom,
            XCB_ATOM_ATOM,
            32,
            1,
            &hidden
        );
      } break;
      case WindowState::Normal: break;
      default: LOG_ERROR("Unknown window state");
    }
  }

  xcb_intern_atom_cookie_t deleteCookie =
      xcb_intern_atom(s_State.connection, 0, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW");
  xcb_intern_atom_cookie_t wmProtocolsCookie =
      xcb_intern_atom(s_State.connection, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");

  xcb_intern_atom_reply_t* deleteReply =
      xcb_intern_atom_reply(s_State.connection, deleteCookie, nullptr);
  xcb_intern_atom_reply_t* wmProtocolsReply =
      xcb_intern_atom_reply(s_State.connection, wmProtocolsCookie, nullptr);

  s_State.wmProtocols    = wmProtocolsReply->atom;
  s_State.wmDeleteWindow = deleteReply->atom;

  PlatformFree(wmProtocolsReply);
  PlatformFree(deleteReply);

  xcb_change_property(
      s_State.connection,
      XCB_PROP_MODE_REPLACE,
      windowId,
      s_State.wmProtocols,
      4,
      32,
      1,
      &s_State.wmDeleteWindow
  );

  *(X11WindowContext*)windowDataHandle = {s_State.connection, s_State.screen, windowId};

  return true;
}

b8 PlatformPollEvents() {
  bool shouldStop{false};
  while (xcb_generic_event_t* event = xcb_poll_for_event(s_State.connection)) {
    switch (event->response_type & ~0x80) {
      case XCB_KEY_PRESS: {
        xcb_key_press_event_t* keyEvent = (xcb_key_press_event_t*)event;
        LOG_INFO("Key pressed: %d", keyEvent->detail);
      } break;
      case XCB_KEY_RELEASE: {
        xcb_key_release_event_t* keyEvent = (xcb_key_release_event_t*)event;
        LOG_INFO("Key released: %d", keyEvent->detail);
        if (keyEvent->detail == 9) {
          shouldStop = true;
        }
      } break;
      case XCB_CLIENT_MESSAGE: {
        xcb_client_message_event_t* clientMessage = (xcb_client_message_event_t*)event;
        if (clientMessage->data.data32[0] == s_State.wmDeleteWindow) {
          LOG_INFO("Window will be closed");
          shouldStop = true;
        }
        break;
      }
    }
  }

  return !shouldStop;
}

void PlatformDestroyNativeWindow(void* windowHandle) {}

void PlatformSleep(u64 ms) {
  usleep(ms * 1000);
}

void* PlatformAlloc(be_size size) {
  return malloc(size);
}

void PlatformFree(void* ptr) {
  free(ptr);
}

} // namespace BE
#endif