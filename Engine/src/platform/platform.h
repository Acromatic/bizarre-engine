#pragma once

#include "core/defines.h"
#include "core/window.h"

namespace BE {

b8 PlatformInit();
void PlatformShutdown();

b8 PlatformCreateNativeWindow(
    const char* title,
    u32 width,
    u32 height,
    i32 x,
    i32 y,
    WindowType type,
    void* windowHandle,
    const Window* parent = nullptr
);
b8 PlatformPollEvents();

void* PlatformAlloc(u64 size);
void PlatformFree(void* ptr);

void PlatformLog(const char* format, ...);
void PlatformLogError(const char* format, ...);

void PlatformSleep(u64 ms);

u64 PlatformGetTimeMs();
} // namespace BE
