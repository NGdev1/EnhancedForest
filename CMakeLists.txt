cmake_minimum_required(VERSION 3.17)
project("EnhancedForest")

set(VENDOR_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Vendor)
set(BIN_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(EnhancedForest)
add_subdirectory(Vendor/bgfx)
add_subdirectory(Vendor/glm)