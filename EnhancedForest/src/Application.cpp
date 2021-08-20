//
//  Application.cpp
//  EnhancedForest
//
//  Created by Admin on 31.07.2021.
//

#include "bgfx_utils.hpp"
#include "entry.hpp"
#include "input.hpp"
#include "imgui/imgui.h"
#include "CoreMesh.hpp"
#include "Common.h"

#include <stdio.h>
#include <bx/uint32_t.h>
#include <bx/math.h>
#include <bx/timer.h>
#include <vector>
#include <iostream>

class ExampleHelloWorld : public entry::AppI {
    entry::MouseState m_mouseState;

    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_debug;
    uint32_t m_reset;

    mat4 view;
    mat4 projectionMatrix;
    mat4 model;
    vec3 clearColor;
    vec3 translate;
    int64_t m_timeOffset;

    CoreMesh *mesh;
    Texture *grass1Texture;
    Shader *baseShader;

public:
    ExampleHelloWorld()
        : entry::AppI()
        , view(1.f)
        , projectionMatrix(1.f)
        , model(1.f) {}

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

        const float SIZE = 8.f;
        static Vertex vertices[24] = {
            // Front
            Vertex(vec3(-SIZE / 2.0f, -SIZE / 2.0f, SIZE / 2.0f), vec2(0.0f, 1.0f)), // 0
            Vertex(vec3(SIZE / 2.0f, -SIZE / 2.0f, SIZE / 2.0f), vec2(1.0f, 1.0f)),  // 1
            Vertex(vec3(SIZE / 2.0f, SIZE / 2.0f, SIZE / 2.0f), vec2(1.0f, 0.0f)),   // 2
            Vertex(vec3(-SIZE / 2.0f, SIZE / 2.0f, SIZE / 2.0f), vec2(0.0f, 0.0f)),  // 3
            // Back
            Vertex(vec3(-SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f), vec2(0.0f, 1.0f)), // 4
            Vertex(vec3(-SIZE / 2.0f, SIZE / 2.0f, -SIZE / 2.0f), vec2(1.0f, 1.0f)),  // 5
            Vertex(vec3(SIZE / 2.0f, SIZE / 2.0f, -SIZE / 2.0f), vec2(1.0f, 0.0f)),   // 6
            Vertex(vec3(SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f), vec2(0.0f, 0.0f)),  // 7
            // Top
            Vertex(vec3(-SIZE / 2.0f, SIZE / 2.0f, -SIZE / 2.0f), vec2(0.0f, 1.0f)), // 8
            Vertex(vec3(-SIZE / 2.0f, SIZE / 2.0f, SIZE / 2.0f), vec2(1.0f, 1.0f)),  // 11
            Vertex(vec3(SIZE / 2.0f, SIZE / 2.0f, SIZE / 2.0f), vec2(1.0f, 0.0f)),   // 10
            Vertex(vec3(SIZE / 2.0f, SIZE / 2.0f, -SIZE / 2.0f), vec2(0.0f, 0.0f)),  // 9
            // Bottom
            Vertex(vec3(-SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f), vec2(0.0f, 1.0f)), // 12
            Vertex(vec3(SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f), vec2(1.0f, 1.0f)),  // 13
            Vertex(vec3(SIZE / 2.0f, -SIZE / 2.0f, SIZE / 2.0f), vec2(1.0f, 0.0f)),   // 14
            Vertex(vec3(-SIZE / 2.0f, -SIZE / 2.0f, SIZE / 2.0f), vec2(0.0f, 0.0f)),  // 15
            // Left
            Vertex(vec3(-SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f), vec2(0.0f, 1.0f)), // 16
            Vertex(vec3(-SIZE / 2.0f, -SIZE / 2.0f, SIZE / 2.0f), vec2(1.0f, 1.0f)),  // 17
            Vertex(vec3(-SIZE / 2.0f, SIZE / 2.0f, SIZE / 2.0f), vec2(1.0f, 0.0f)),   // 18
            Vertex(vec3(-SIZE / 2.0f, SIZE / 2.0f, -SIZE / 2.0f), vec2(0.0f, 0.0f)),  // 19
            // Right
            Vertex(vec3(SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f), vec2(0.0f, 1.0f)), // 20
            Vertex(vec3(SIZE / 2.0f, SIZE / 2.0f, -SIZE / 2.0f), vec2(1.0f, 1.0f)),  // 23
            Vertex(vec3(SIZE / 2.0f, SIZE / 2.0f, SIZE / 2.0f), vec2(1.0f, 0.0f)),   // 22
            Vertex(vec3(SIZE / 2.0f, -SIZE / 2.0f, SIZE / 2.0f), vec2(0.0f, 0.0f))   // 21
        };

        static uint16_t indices[36] = {
            2, 1, 0, 0, 3, 2,       // Front
            6, 5, 4, 4, 7, 6,       // Back
            10, 9, 8, 8, 11, 10,    // Top
            14, 13, 12, 12, 15, 14, // Bottom
            18, 17, 16, 16, 19, 18, // Left
            22, 21, 20, 20, 23, 22  // Right
        };

        grass1Texture = new Texture("arbuz1.png");
        std::vector<Texture *> textures;
        textures.push_back(grass1Texture);

        baseShader = new Shader("base_vertex", "base_fragment");
        bx::mtxProj(&projectionMatrix[0][0], 60.0f, float(m_width) / float(m_height), 0.1f, 1000.0f, bgfx::getCaps()->homogeneousDepth);

        mesh = new CoreMesh(vertices, 24, indices, 36, textures, baseShader);
        m_timeOffset = bx::getHPCounter();
    }

    virtual int shutdown() override {
        imguiDestroy();
        delete baseShader;
        delete grass1Texture;
        delete mesh;
        bgfx::shutdown();
        return 0;
    }

    void update() override {
        entry::pollEvents(m_width, m_height, m_debug, m_reset, &m_mouseState);
        if (inputGetKeyState(entry::Key::KeyQ)) {
            entry::setAppShouldClose();
        }

        float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

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

        const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
        const bx::Vec3 eye = {0.0f, 0.0f, 15.0f};
        bx::mtxLookAt(&view[0][0], eye, at);
        bgfx::setViewTransform(0, &view[0][0], &projectionMatrix[0][0]);
        bx::mtxRotateXY(&model[0][0], time, time);

        view[3][0] = translate.x;
        view[3][1] = translate.y;
        view[3][2] = translate.z;

        bgfx::setTransform(&model[0][0]);

        mesh->draw();

        bgfx::frame();
    }
};

int startApp(int _argc, char **_argv) {
    ExampleHelloWorld app;
    return entry::runApp(&app, _argc, _argv);
}
