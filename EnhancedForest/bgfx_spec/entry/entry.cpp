//
//  entry.cpp
//  EnhancedForest
//
//  Created by Admin on 31.07.2021.
//

#include <bgfx/bgfx.h>

#include <time.h>

#include "event_queue.hpp"
#include "input.hpp"
#include "filesystem/fileio.hpp"
#include "allocator/bxallocator.hpp"

extern "C" int32_t startApp(int32_t _argc, char **_argv);

namespace entry {

static uint32_t s_debug = BGFX_DEBUG_NONE;
static uint32_t s_reset = BGFX_RESET_NONE;
static uint32_t s_width = ENTRY_DEFAULT_WIDTH;
static uint32_t s_height = ENTRY_DEFAULT_HEIGHT;

static AppI *s_app = NULL;

AppI::AppI() {
    s_app = this;
}

AppI::~AppI() {}

int runApp(AppI *_app, int _argc, const char *const *_argv) {
    _app->init(_argc, _argv, s_width, s_height);
    bgfx::frame();

    WindowHandle defaultWindow = {0};
    setWindowSize(defaultWindow, s_width, s_height);

    while (_app->update())
        ;

    return _app->shutdown();
}

int main(int _argc, const char *const *_argv) {
    DBG(BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME);

    fileIoInit();
    inputInit();

    entry::WindowHandle defaultWindow = {0};

    // toggleFullscreen(defaultWindow);
    setWindowSize(defaultWindow, ENTRY_DEFAULT_WIDTH, ENTRY_DEFAULT_HEIGHT);

    const char *find = "";
    if (1 < _argc) {
        find = _argv[_argc - 1];
    }

    int32_t result = bx::kExitSuccess;
    result = ::startApp(_argc, (char **)_argv);

    setCurrentDir("");

    inputShutdown();
    fileIoDeinit();

    return result;
}

WindowState s_window[ENTRY_CONFIG_MAX_WINDOWS];

bool pollEvents(uint32_t &_width, uint32_t &_height, uint32_t &_debug, uint32_t &_reset, MouseState *_mouse) {
    bool needReset = s_reset != _reset;

    s_debug = _debug;
    s_reset = _reset;

    WindowHandle handle = {UINT16_MAX};

    bool mouseLock = inputIsMouseLocked();

    const Event *ev;
    do {
        struct SE {
            const Event *m_ev;
            SE()
                : m_ev(poll()) {}
            ~SE() {
                if (NULL != m_ev) {
                    release(m_ev);
                }
            }
        } scopeEvent;
        ev = scopeEvent.m_ev;

        if (NULL != ev) {
            switch (ev->m_type) {
                case Event::Axis: {
                    const AxisEvent *axis = static_cast<const AxisEvent *>(ev);
                    inputSetGamepadAxis(axis->m_gamepad, axis->m_axis, axis->m_value);
                } break;

                case Event::Char: {
                    const CharEvent *chev = static_cast<const CharEvent *>(ev);
                    inputChar(chev->m_len, chev->m_char);
                } break;

                case Event::Exit:
                    return true;

                case Event::Gamepad: {
                    //                        const GamepadEvent* gev = static_cast<const GamepadEvent*>(ev);
                    //                        DBG("gamepad %d, %d", gev->m_gamepad.idx, gev->m_connected);
                } break;

                case Event::Mouse: {
                    const MouseEvent *mouse = static_cast<const MouseEvent *>(ev);
                    handle = mouse->m_handle;

                    inputSetMousePos(mouse->m_mx, mouse->m_my, mouse->m_mz);
                    if (!mouse->m_move) {
                        inputSetMouseButtonState(mouse->m_button, mouse->m_down);
                    }

                    if (NULL != _mouse && !mouseLock) {
                        _mouse->m_mx = mouse->m_mx;
                        _mouse->m_my = mouse->m_my;
                        _mouse->m_mz = mouse->m_mz;
                        if (!mouse->m_move) {
                            _mouse->m_buttons[mouse->m_button] = mouse->m_down;
                        }
                    }
                } break;

                case Event::Key: {
                    const KeyEvent *key = static_cast<const KeyEvent *>(ev);
                    handle = key->m_handle;

                    inputSetKeyState(key->m_key, key->m_modifiers, key->m_down);
                } break;

                case Event::Size: {
                    const SizeEvent *size = static_cast<const SizeEvent *>(ev);
                    WindowState &win = s_window[0];
                    win.m_handle = size->m_handle;
                    win.m_width = size->m_width;
                    win.m_height = size->m_height;

                    handle = size->m_handle;
                    _width = size->m_width;
                    _height = size->m_height;

                    needReset = true;
                } break;

                case Event::Window:
                    break;

                case Event::Suspend:
                    break;

                case Event::DropFile: {
                    const DropFileEvent *drop = static_cast<const DropFileEvent *>(ev);
                    DBG("%s", drop->m_filePath.getCPtr());
                } break;

                default:
                    break;
            }
        }

    } while (NULL != ev);

    needReset |= _reset != s_reset;

    if (handle.idx == 0 && needReset) {
        _reset = s_reset;
        bgfx::reset(_width, _height, _reset);
        inputSetMouseResolution(uint16_t(_width), uint16_t(_height));
    }

    _debug = s_debug;

    s_width = _width;
    s_height = _height;

    return false;
}

} // namespace entry
