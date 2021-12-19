cmake_minimum_required(VERSION 3.14)

add_library(zGlad "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")

target_include_directories(zGlad PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)