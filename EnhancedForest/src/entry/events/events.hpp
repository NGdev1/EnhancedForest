//
//  events.hpp
//  EnhancedForest
//
//  Created by Admin on 06.08.2021.
//

#pragma once

#include <bx/filepath.h>

#include "window.hpp"
#include "base_enums.hpp"

#define ENTRY_IMPLEMENT_EVENT(_class, _type)                                                                                               \
    _class(WindowHandle _handle)                                                                                                           \
        : Event(_type, _handle) {}

namespace entry {

struct Event {
    enum Enum {
        Axis,
        Char,
        Exit,
        Gamepad,
        Key,
        Mouse,
        Size,
        Window,
        Suspend,
        DropFile,
    };

    Event(Enum _type)
        : m_type(_type) {
        m_handle.idx = UINT16_MAX;
    }

    Event(Enum _type, WindowHandle _handle)
        : m_type(_type)
        , m_handle(_handle) {}

    Event::Enum m_type;
    WindowHandle m_handle;
};

struct AxisEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(AxisEvent, Event::Axis);

    GamepadAxis::Enum m_axis;
    int32_t m_value;
    GamepadHandle m_gamepad;
};

struct CharEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(CharEvent, Event::Char);

    uint8_t m_len;
    uint8_t m_char[4];
};

struct GamepadEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(GamepadEvent, Event::Gamepad);

    GamepadHandle m_gamepad;
    bool m_connected;
};

struct KeyEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(KeyEvent, Event::Key);

    Key::Enum m_key;
    uint8_t m_modifiers;
    bool m_down;
};

struct MouseEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(MouseEvent, Event::Mouse);

    int32_t m_mx;
    int32_t m_my;
    int32_t m_mz;
    MouseButton::Enum m_button;
    bool m_down;
    bool m_move;
};

struct SizeEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(SizeEvent, Event::Size);

    uint32_t m_width;
    uint32_t m_height;
};

struct WindowEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(WindowEvent, Event::Window);

    void *m_nwh;
};

struct SuspendEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(SuspendEvent, Event::Suspend);

    Suspend::Enum m_state;
};

struct DropFileEvent : public Event {
    ENTRY_IMPLEMENT_EVENT(DropFileEvent, Event::DropFile);

    bx::FilePath m_filePath;
};

} // namespace entry
