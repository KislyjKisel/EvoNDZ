cmake_minimum_required(VERSION 3.8)

project(EvoNDZ VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(THIRDPARTY_LIBS_DIR "Debug")
else()
    set(THIRDPARTY_LIBS_DIR "Release")
endif()

file(GLOB THIRDPARTY_LIBS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/third_party/lib/${THIRDPARTY_LIBS_DIR}/*.lib")

add_subdirectory("EvoNDZ")
add_subdirectory("EvoNDZ Test")
add_subdirectory("third_party/zGlad")