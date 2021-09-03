project(Sandbox)

set(CMAKE_CXX_STANDARD 14)
file(GLOB_RECURSE SOURCES
        src/*.cpp
        src/*.mm
        src/*.h
        src/*.hpp
        bgfx_spec/*.cpp
        bgfx_spec/*.mm
        bgfx_spec/*.h
        bgfx_spec/*.hpp
        )

# Storybrooke target
add_executable(Sandbox ${SOURCES})
target_include_directories(Sandbox PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Sandbox PRIVATE ${PROJECT_SOURCE_DIR}/bgfx_spec)

set_target_properties(Sandbox
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${BIN_DIRECTORY}
        )

# Dependencies - bgfx
target_link_libraries(Sandbox bgfx)
target_include_directories(Sandbox PRIVATE ${VENDOR_DIRECTORY}/bgfx/bgfx/include)
target_include_directories(Sandbox PRIVATE ${VENDOR_DIRECTORY}/bgfx/bgfx/3rdparty)
target_include_directories(Sandbox PRIVATE ${VENDOR_DIRECTORY}/bgfx/bimg/include)
target_include_directories(Sandbox PRIVATE ${VENDOR_DIRECTORY}/bgfx/bx/include)

# Dependencies - meshoptimizer
target_link_libraries(Sandbox meshoptimizer)

# Dependencies - dear-imgui
target_link_libraries(Sandbox dear-imgui)

# Dependencies - glm
target_link_libraries(Sandbox glm)
target_include_directories(Sandbox PRIVATE ${VENDOR_DIRECTORY}/glm)