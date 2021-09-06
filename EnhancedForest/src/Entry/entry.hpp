//
//  entry.hpp
//  EnhancedForest
//
//  Created by Admin on 31.07.2021.
//

#pragma once

#include "dbg.hpp"
#include "enums/base_enums.hpp"
#include "window/window.hpp"

extern int startApp(int _argc, char **_argv);

namespace entry {

void pollEvents(uint32_t &_width, uint32_t &_height, uint32_t &_debug, uint32_t &_reset, MouseState *_mouse = NULL);

bool appShouldClose();

void setAppShouldClose();

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
    virtual void update() = 0;
};

///
int runApp(AppI *_app, int _argc, const char *const *_argv);

} // namespace entry
