//
//  window.hpp
//  EnhancedForest
//
//  Created by Admin on 06.08.2021.
//

#pragma once

#include <bx/filepath.h>

namespace entry {

struct WindowHandle {
    uint16_t idx;
};

struct GamepadHandle {
    uint16_t idx;
};

inline bool isValid(WindowHandle _handle) {
    return UINT16_MAX != _handle.idx;
}

inline bool isValid(GamepadHandle _handle) {
    return UINT16_MAX != _handle.idx;
}

struct GamepadState {
    GamepadState() {
        bx::memSet(m_axis, 0, sizeof(m_axis));
    }

    int32_t m_axis[entry::GamepadAxis::Count];
};

struct WindowState {
    WindowState()
        : m_width(0)
        , m_height(0)
        , m_nwh(NULL) {
        m_handle.idx = UINT16_MAX;
    }

    WindowHandle m_handle;
    uint32_t m_width;
    uint32_t m_height;
    MouseState m_mouse;
    void *m_nwh;
    bx::FilePath m_dropFile;
};

} // namespace entry
