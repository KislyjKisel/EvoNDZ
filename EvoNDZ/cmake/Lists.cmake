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

set(EvoNDZ_INC
    # app
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/app/application.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/app/glad_exception.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/app/glfw_exception.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/app/scene.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/app/window.h"

    # cli
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/cli/command_group.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/cli/command_manager.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/cli/command_task.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/cli/util.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/cli/wait_for_input.h"

    # content
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/archive.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/content.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/content_storage.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/loader_base.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/loader_manager.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/loading.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/mesh.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/name.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/reference.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/serialization.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/shader.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/storage.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/storage_manager.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/content/texture2d.h"

    # data
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/data/array.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/data/lazy.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/data/limited_stack.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/data/open_hash_table.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/data/open_map.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/data/open_set.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/data/property.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/data/util.h"

    # debug
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/debug/logger.h"

    # functional
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/functional/function.h"

    # graphics
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/blend_equation.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/blend_factor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/buffer_bit.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/buffer_usage.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/capability.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/depth_function.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/draw_mode.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/logical_pixel_operation.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/shader_type.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/storage_flags.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/enum/texture_format.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/dynamic_vertex_buffer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/index_buffer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/index_type.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/mesh.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/parameters.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/render_target.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/state.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/technique.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/texture2d.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/types.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/vertex_array.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/opengl/vertex_buffer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/simple2d/plain_color_2d_batch.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/simple2d/renderer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/simple2d/shape_batch.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/batch.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/graphics/camera2d.h"

    # input
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/input/input.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/input/key.h"

    # math 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/ball.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/box.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/concepts.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/figure.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/geometry.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/line.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/line_equation.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/math.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/matrix3.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/matrix4.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/point.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/quaternion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/ray.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/segment.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/traits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/triangle.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/vector.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/vector2.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/vector3.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/math/vector4.h"

    # meta
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/meta/assumption.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/meta/macro.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/meta/sstring.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/meta/type_pack.h"

    # util
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/array.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/bytes.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/color3.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/color4.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/compiler.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/concepts.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/enum.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/event.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/exception.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/integer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/platform.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/string_key.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/timer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/type_traits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ/util/util.h"
   )