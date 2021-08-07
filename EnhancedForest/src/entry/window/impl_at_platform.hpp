//
//  impl_at_platform.hpp
//  EnhancedForest
//
//  Created by Admin on 07.08.2021.
//

#pragma once

#include "events.hpp"

#ifndef ENTRY_CONFIG_USE_NOOP
#    define ENTRY_CONFIG_USE_NOOP 0
#endif // ENTRY_CONFIG_USE_NOOP

#ifndef ENTRY_CONFIG_USE_SDL
#    define ENTRY_CONFIG_USE_SDL 0
#endif // ENTRY_CONFIG_USE_SDL

#ifndef ENTRY_CONFIG_USE_GLFW
#    define ENTRY_CONFIG_USE_GLFW 0
#endif // ENTRY_CONFIG_USE_GLFW

#ifndef ENTRY_CONFIG_USE_WAYLAND
#    define ENTRY_CONFIG_USE_WAYLAND 0
#endif // ENTRY_CONFIG_USE_WAYLAND

#if !defined(ENTRY_CONFIG_USE_NATIVE) && !ENTRY_CONFIG_USE_NOOP && !ENTRY_CONFIG_USE_SDL && !ENTRY_CONFIG_USE_GLFW
#    define ENTRY_CONFIG_USE_NATIVE 1
#else
#    define ENTRY_CONFIG_USE_NATIVE 0
#endif // ...

#ifndef ENTRY_CONFIG_MAX_WINDOWS
#    define ENTRY_CONFIG_MAX_WINDOWS 8
#endif // ENTRY_CONFIG_MAX_WINDOWS

#ifndef ENTRY_CONFIG_MAX_GAMEPADS
#    define ENTRY_CONFIG_MAX_GAMEPADS 4
#endif // ENTRY_CONFIG_MAX_GAMEPADS

#if !defined(ENTRY_DEFAULT_WIDTH) && !defined(ENTRY_DEFAULT_HEIGHT)
#    define ENTRY_DEFAULT_WIDTH 1280
#    define ENTRY_DEFAULT_HEIGHT 720
#elif !defined(ENTRY_DEFAULT_WIDTH) || !defined(ENTRY_DEFAULT_HEIGHT)
#    error "Both ENTRY_DEFAULT_WIDTH and ENTRY_DEFAULT_HEIGHT must be defined."
#endif // ENTRY_DEFAULT_WIDTH

#ifndef ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR
#    define ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR 1
#endif // ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR

#ifndef ENTRY_CONFIG_PROFILER
#    define ENTRY_CONFIG_PROFILER 0
#endif // ENTRY_CONFIG_PROFILER

namespace entry {

int main(int _argc, const char *const *_argv);

const Event *poll();

const Event *poll(WindowHandle _handle);

void release(const Event *_event);

} // namespace entry
