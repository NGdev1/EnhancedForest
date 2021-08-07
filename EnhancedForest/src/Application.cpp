//
//  Application.cpp
//  EnhancedForest
//
//  Created by Admin on 31.07.2021.
//

#include <stdio.h>
#include <bx/uint32_t.h>

#include "bgfx_utils.hpp"
#include "entry.hpp"
#include "input.hpp"
#include "imgui/imgui.h"

class ExampleHelloWorld : public entry::AppI {
    entry::MouseState m_mouseState;

    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_debug;
    uint32_t m_reset;

public:
    ExampleHelloWorld()
        : entry::AppI() {}

    void init(int32_t _argc, const char *const *_argv, uint32_t _width, uint32_t _height) override {
        Args args(_argc, _argv);

        m_width = _width;
        m_height = _height;
        m_debug = BGFX_DEBUG_TEXT;
        m_reset = BGFX_RESET_VSYNC;

        bgfx::Init init;
        init.type = args.m_type;
        init.vendorId = args.m_pciId;
        init.resolution.width = m_width;
        init.resolution.height = m_height;
        init.resolution.reset = m_reset;
        bgfx::init(init);
        bgfx::setDebug(m_debug);
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x173343ff, 1.0f, 0);

        imguiCreate();
    }

    virtual int shutdown() override {
        imguiDestroy();
        bgfx::shutdown();
        return 0;
    }

    void update() override {
        entry::pollEvents(m_width, m_height, m_debug, m_reset, &m_mouseState);
        if (inputGetKeyState(entry::Key::KeyQ)) {
            entry::setAppShouldClose();
        }

        imguiBeginFrame(m_mouseState.m_mx, m_mouseState.m_my,
            (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0) |
                (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0) |
                (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0),
            m_mouseState.m_mz, uint16_t(m_width), uint16_t(m_height));

        showExampleDialog();

        ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_FirstUseEver);
        ImGui::Begin("W1");
        if (ImGui::Button("EXIT")) {
            entry::setAppShouldClose();
        }
        ImGui::End();

        imguiEndFrame();

        bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
        bgfx::touch(0);

        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(2, 2, 0x0f, "Hello, world!");

        bgfx::frame();
    }
};

int startApp(int _argc, char **_argv) {
    ExampleHelloWorld app;
    return entry::runApp(&app, _argc, _argv);
}
