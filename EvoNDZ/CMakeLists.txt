cmake_minimum_required(VERSION 3.14)

file(GLOB_RECURSE EvoNDZ_SRC "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp")

add_library(EvoNDZ ${EvoNDZ_SRC})


target_include_directories(EvoNDZ PUBLIC 
                           "${CMAKE_CURRENT_SOURCE_DIR}/include"
                           "${CMAKE_SOURCE_DIR}/third_party/include"
                          )

target_link_libraries(EvoNDZ PUBLIC glad)