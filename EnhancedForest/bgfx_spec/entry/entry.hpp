//
//  entry.hpp
//  EnhancedForest
//
//  Created by Admin on 31.07.2021.
//

#pragma once

#include "dbg.hpp"
#include "base_enums.hpp"
#include "window/window.hpp"

extern "C" int startApp(int _argc, char **_argv);

#define ENTRY_WINDOW_FLAG_NONE UINT32_C(0x00000000)
#define ENTRY_WINDOW_FLAG_ASPECT_RATIO UINT32_C(0x00000001)
#define ENTRY_WINDOW_FLAG_FRAME UINT32_C(0x00000002)

namespace entry {

bool pollEvents(uint32_t &_width, uint32_t &_height, uint32_t &_debug, uint32_t &_reset, MouseState *_mouse = NULL);

WindowHandle createWindow(
    int32_t _x, int32_t _y, uint32_t _width, uint32_t _height, uint32_t _flags = ENTRY_WINDOW_FLAG_NONE, const char *_title = "");
void destroyWindow(WindowHandle _handle);
void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y);
void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height);
void setWindowTitle(WindowHandle _handle, const char *_title);
void setWindowFlags(WindowHandle _handle, uint32_t _flags, bool _enabled);
void toggleFullscreen(WindowHandle _handle);
void setMouseLock(WindowHandle _handle, bool _lock);
void setCurrentDir(const char *_dir);

class BX_NO_VTABLE AppI {
public:
    ///
    AppI();

    ///
    virtual ~AppI() = 0;

    ///
    virtual void init(int32_t _argc, const char *const *_argv, uint32_t _width, uint32_t _height) = 0;

    ///
    virtual int shutdown() = 0;

    ///
    virtual bool update() = 0;
};

///
int runApp(AppI *_app, int _argc, const char *const *_argv);

} // namespace entry
