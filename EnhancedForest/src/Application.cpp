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
#include "Camera.hpp"
#include "impl_at_platform.hpp"

#include <stdio.h>
#include <bx/uint32_t.h>
#include <bx/math.h>
#include <bx/timer.h>
#include <vector>
#include <iostream>

namespace ef {

class ExampleHelloWorld : public entry::AppI {
    entry::MouseState m_mouseState;
    entry::MouseState m_lastMouseState;

    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_debug;
    uint32_t m_reset;

    mat4 m_projectionMatrix;
    mat4 m_model;
    vec3 m_clearColor;
    int64_t m_programStartedTime;
    int64_t m_lastFrameTime;

    CoreMesh *m_mesh;
    Texture *m_grass1Texture;
    Shader *m_baseShader;
    Camera m_camera;
    float m_cameraSpeed;
    float m_mouseSpeed;

    float m_rotationX;
    float m_rotationY;

public:
    ExampleHelloWorld()
        : entry::AppI()
        , m_projectionMatrix(1.f)
        , m_model(1.f)
        , m_camera(glm::vec3(0.f, 0.f, -25.f))
        , m_cameraSpeed(15.f)
        , m_mouseSpeed(100.f)
        , m_rotationX(0.f)
        , m_rotationY(0.f) {}

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

        m_grass1Texture = new Texture("textures/arbuz1.png");

        m_baseShader = new Shader("base_vertex", "base_fragment");
        bx::mtxProj(&m_projectionMatrix[0][0], 60.0f, float(m_width) / float(m_height), 0.1f, 1000.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

        m_mesh = new CoreMesh(vertices, 24, indices, 36, m_grass1Texture, m_baseShader);

        m_programStartedTime = bx::getHPCounter();
        m_lastFrameTime = bx::getHPCounter();

        m_mouseState.m_mx = _width / 2;
        m_mouseState.m_my = _height / 2;
        m_lastMouseState = m_mouseState;
        inputSetMousePos(_height / 2, _width / 2, 1);
    }

    int shutdown() override {
        imguiDestroy();
        delete m_baseShader;
        delete m_grass1Texture;
        delete m_mesh;
        bgfx::shutdown();
        return 0;
    }

    void update() override {
        // step 1: Time caclulations
        float deltaTime = float(bx::getHPCounter() - m_lastFrameTime) / float(bx::getHPFrequency());
        m_lastFrameTime = bx::getHPCounter();
        float time = (float)((bx::getHPCounter() - m_programStartedTime) / double(bx::getHPFrequency()));

        // step 2: input poll events
        m_lastMouseState = m_mouseState;
        entry::pollEvents(m_width, m_height, m_debug, m_reset, &m_mouseState);

        // step 3: input process
        if (inputGetKeyState(entry::Key::KeyQ)) {
            entry::setAppShouldClose();
        }
        if (inputGetKeyState(entry::Key::KeyW)) {
            m_camera.position -= deltaTime * m_cameraSpeed * m_camera.front;
        }
        if (inputGetKeyState(entry::Key::KeyS)) {
            m_camera.position += deltaTime * m_cameraSpeed * m_camera.front;
        }
        if (inputGetKeyState(entry::Key::KeyA)) {
            m_camera.position -= deltaTime * m_cameraSpeed * m_camera.right;
        }
        if (inputGetKeyState(entry::Key::KeyD)) {
            m_camera.position += deltaTime * m_cameraSpeed * m_camera.right;
        }

        if (m_mouseState.m_buttons[entry::MouseButton::Left]) {
            float mouseDeltaX = m_mouseState.m_mx - m_lastMouseState.m_mx;
            float mouseDeltaY = m_mouseState.m_my - m_lastMouseState.m_my;
            m_rotationX += (mouseDeltaY / m_height) * deltaTime * m_mouseSpeed;
            m_rotationY -= (mouseDeltaX / m_width) * deltaTime * m_mouseSpeed;
            m_camera.rotation = glm::mat4(1.f);
            m_camera.rotate(m_rotationX, m_rotationY, 0.f);
        }

        // step 4: render frame
        // imguiBeginFrame(m_mouseState.m_mx, m_mouseState.m_my,
        //     (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0) |
        //         (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0) |
        //         (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0),
        //     m_mouseState.m_mz, uint16_t(m_width), uint16_t(m_height));
        //
        // showExampleDialog();
        //
        // ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_FirstUseEver);
        // ImGui::Begin("W1");
        // if (ImGui::Button("EXIT")) {
        //     entry::setAppShouldClose();
        // }
        // ImGui::End();
        //
        // imguiEndFrame();

        bgfx::touch(0);
        bx::mtxProj(&m_projectionMatrix[0][0], 60.0f, float(m_width) / float(m_height), 0.1f, 1000.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
        glm::mat4 view = m_camera.getView();
        bgfx::setViewTransform(0, &view[0][0], &m_projectionMatrix[0][0]);
        bx::mtxRotateXY(&m_model[0][0], time, time);

        bgfx::setTransform(&m_model[0][0]);

        m_mesh->draw();

        bgfx::frame();
    }
};

} // namespace ef

int startApp(int _argc, char **_argv) {
    ef::ExampleHelloWorld app;
    return entry::runApp(&app, _argc, _argv);
}
