cmake_minimum_required(VERSION 3.14)

set(EvoNDZ_SRC 
    #
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui.cpp"

    # app
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/app/application.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/app/window.cpp"

    # content
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/content/archive.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/content/content.cpp"

    # graphics
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/batch.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/dynamic_vertex_buffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/index_buffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/index_type.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/parameters.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/render_target.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/technique.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/texture2d.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/vertex_array.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/vertex_buffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/opengl/enum/enum.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/simple2d/plain_color_2d_batch.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/graphics/simple2d/renderer.cpp"
    
    # input
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/input/input.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/input/key_names.cpp"
    
    # math
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/math/math.cpp"

    # util
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/util/util.cpp"
   )

add_library(EvoNDZ ${EvoNDZ_SRC})

target_include_directories(EvoNDZ PUBLIC 
                           "${CMAKE_CURRENT_SOURCE_DIR}/include"
                           "${CMAKE_SOURCE_DIR}/third_party/include"
                          )

target_link_libraries(EvoNDZ PUBLIC glad)

target_precompile_headers(EvoNDZ PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/pch.h")