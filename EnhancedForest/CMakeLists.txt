project(EnhancedForest)

include(cmake/add_app.cmake)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES
        src/*.cpp
        src/*.mm
        )

file(GLOB_RECURSE INCLUDE
        src/*.h
        src/*.hpp
        )

file(GLOB RESOURCE_FOLDERS
        Resources-common/*
        Resources-pc/*
        )
list(FILTER RESOURCE_FOLDERS EXCLUDE REGEX "\\.DS_Store")

# Storybrooke target

add_app(EnhancedForest "${SOURCES}" "${INCLUDE}" "${RESOURCE_FOLDERS}")

target_include_directories(EnhancedForest PRIVATE ${PROJECT_SOURCE_DIR}/src)

set_target_properties(EnhancedForest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${BIN_DIRECTORY}
        )

# Dependencies - bgfx
target_link_libraries(EnhancedForest bgfx)
target_include_directories(EnhancedForest PRIVATE ${VENDOR_DIRECTORY}/bgfx/bgfx/include)
target_include_directories(EnhancedForest PRIVATE ${VENDOR_DIRECTORY}/bgfx/bgfx/3rdparty)
target_include_directories(EnhancedForest PRIVATE ${VENDOR_DIRECTORY}/bgfx/bimg/include)
target_include_directories(EnhancedForest PRIVATE ${VENDOR_DIRECTORY}/bgfx/bx/include)

# Dependencies - meshoptimizer
target_link_libraries(EnhancedForest meshoptimizer)

# Dependencies - dear-imgui
target_link_libraries(EnhancedForest dear-imgui)

# Dependencies - glm
target_link_libraries(EnhancedForest glm)
target_include_directories(EnhancedForest PRIVATE ${VENDOR_DIRECTORY}/glm)