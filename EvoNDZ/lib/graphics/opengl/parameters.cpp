#include "../../../include/EvoNDZ/graphics/opengl/parameters.h"
#include <glad/glad.h>
#include "../../../include/EvoNDZ/meta/macro.h"

namespace evo::ogl
{
	gl_boolean_t Parameters::is_enabled(Capability c) {
		return glIsEnabled(c.value());
	}
	gl_boolean_t Parameters::is_enabled(Capability c, gl_uint_t index) {
		return glIsEnabledi(c.value(), index);
	}

	Parameters::Parameters() {
		glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, this->msp_aliased_line_width_range.data());
		glGetIntegerv(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, &this->msp_max_compute_shader_storage_blocks);
		glGetIntegerv(GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS, &this->msp_max_combined_shader_storage_blocks);
		glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_BLOCKS, &this->msp_max_compute_uniform_blocks);
		glGetIntegerv(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, &this->msp_max_compute_texture_image_units);
		glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_COMPONENTS, &this->msp_max_compute_uniform_components);
		glGetIntegerv(GL_MAX_COMPUTE_ATOMIC_COUNTERS, &this->msp_max_compute_atomic_counters);
		glGetIntegerv(GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS, &this->msp_max_compute_atomic_counter_buffers);
		glGetIntegerv(GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS, &this->msp_max_combined_compute_uniform_components);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &this->msp_max_compute_work_group_count_x); 
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &this->msp_max_compute_work_group_count_y);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &this->msp_max_compute_work_group_count_z);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &this->msp_max_compute_work_group_size_x);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &this->msp_max_compute_work_group_size_y);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &this->msp_max_compute_work_group_size_z);
		glGetIntegerv(GL_MAX_DEBUG_GROUP_STACK_DEPTH, &this->msp_max_debug_group_stack_depth);
		glGetIntegerv(GL_CONTEXT_FLAGS, &this->msp_context_flags);
		glGetBooleanv(GL_DOUBLEBUFFER, &this->msp_doublebuffer);
		glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &this->msp_implementation_color_read_format);
		glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &this->msp_implementation_color_read_type);
		glGetIntegerv(GL_LAYER_PROVOKING_VERTEX, &this->msp_layer_provoking_vertex);
		glGetIntegerv(GL_MAJOR_VERSION, &this->msp_api_major_version);
		glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &this->msp_max_3d_texture_size);
		glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &this->msp_max_array_texture_layers);
		glGetIntegerv(GL_MAX_CLIP_DISTANCES, &this->msp_max_clip_distances);
		glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &this->msp_max_color_texture_samples);
		glGetIntegerv(GL_MAX_COMBINED_ATOMIC_COUNTERS, &this->msp_max_combined_atomic_counters);
		glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, &this->msp_max_combined_fragment_uniform_components);
		glGetIntegerv(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS, &this->msp_max_combined_geometry_uniform_components);
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &this->msp_max_combined_texture_image_units);
		glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &this->msp_max_combined_uniform_blocks);
		glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, &this->msp_max_combined_vertex_uniform_components);
		glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &this->msp_max_cube_map_texture_size);
		glGetIntegerv(GL_MAX_DEPTH_TEXTURE_SAMPLES, &this->msp_max_depth_texture_samples);
		glGetIntegerv(GL_MAX_DRAW_BUFFERS, &this->msp_max_draw_buffers);
		glGetIntegerv(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, &this->msp_max_dual_source_draw_buffers);
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &this->msp_max_elements_indices);
		glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &this->msp_max_elements_vertices);
		glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTERS, &this->msp_max_fragment_atomic_counters);
		glGetIntegerv(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, &this->msp_max_fragment_shader_storage_blocks);
		glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS, &this->msp_max_fragment_input_components);
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &this->msp_max_fragment_uniform_components);
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &this->msp_max_fragment_uniform_vectors);
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &this->msp_max_fragment_uniform_blocks);
		glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &this->msp_max_framebuffer_width);
		glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &this->msp_max_framebuffer_height);
		glGetIntegerv(GL_MAX_FRAMEBUFFER_LAYERS, &this->msp_max_framebuffer_layers);
		glGetIntegerv(GL_MAX_FRAMEBUFFER_SAMPLES, &this->msp_max_framebuffer_samples);
		glGetIntegerv(GL_MAX_GEOMETRY_ATOMIC_COUNTERS, &this->msp_max_geometry_atomic_counters);
		glGetIntegerv(GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS, &this->msp_max_geometry_shader_storage_blocks);
		glGetIntegerv(GL_MAX_GEOMETRY_INPUT_COMPONENTS, &this->msp_max_geometry_input_components);
		glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, &this->msp_max_geometry_output_components);
		glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, &this->msp_max_geometry_texture_image_units);
		glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &this->msp_max_geometry_uniform_blocks);
		glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &this->msp_max_geometry_uniform_components);
		glGetIntegerv(GL_MAX_INTEGER_SAMPLES, &this->msp_max_integer_samples);
		glGetIntegerv(GL_MIN_MAP_BUFFER_ALIGNMENT, &this->msp_min_map_buffer_alignment);
		glGetIntegerv(GL_MAX_LABEL_LENGTH, &this->msp_max_label_length);
		glGetIntegerv(GL_MAX_PROGRAM_TEXEL_OFFSET, &this->msp_max_program_texel_offset);
		glGetIntegerv(GL_MIN_PROGRAM_TEXEL_OFFSET, &this->msp_min_program_textel_offset);
		glGetIntegerv(GL_MAX_RECTANGLE_TEXTURE_SIZE, &this->msp_max_rectangle_texture_size);
		glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &this->msp_max_renderbuffer_size);
		glGetIntegerv(GL_MAX_SAMPLE_MASK_WORDS, &this->msp_max_sample_mask_words);
		glGetIntegerv(GL_MAX_SERVER_WAIT_TIMEOUT, &this->msp_max_server_wait_timeout);
		glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &this->msp_max_shader_storage_buffer_bindings);
		glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS, &this->msp_max_tess_control_atomic_counters);
		glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS, &this->msp_max_tess_evaluation_atomic_counters);
		glGetIntegerv(GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS, &this->msp_max_tess_control_shader_storage_blocks);
		glGetIntegerv(GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS, &this->msp_max_tess_evaluation_shader_storage_blocks);
		glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &this->msp_max_texture_buffer_size);
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &this->msp_max_texture_image_units);
		glGetIntegerv(GL_MAX_TEXTURE_LOD_BIAS, &this->msp_max_texture_lod_bias);
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &this->msp_max_texture_size);
		glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &this->msp_max_uniform_buffer_bindings);
		glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &this->msp_max_uniform_block_size);
		glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &this->msp_max_uniform_locations);
		glGetIntegerv(GL_MAX_VARYING_COMPONENTS, &this->msp_max_varying_components);
		glGetIntegerv(GL_MAX_VARYING_VECTORS, &this->msp_max_varying_vectors);
		glGetIntegerv(GL_MAX_VARYING_FLOATS, &this->msp_max_varying_floats);
		glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTERS, &this->msp_max_vertex_atomic_counters);
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &this->msp_max_vertex_attribs);
		glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &this->msp_max_vertex_shader_storage_blocks);
		glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &this->msp_max_vertex_texture_image_units);
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &this->msp_max_vertex_uniform_components);
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &this->msp_max_vertex_uniform_vectors);
		glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &this->msp_max_vertex_output_components);
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &this->msp_max_vertex_uniform_blocks);
		glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &this->msp_max_viewport_dims);
		glGetIntegerv(GL_MAX_VIEWPORTS, &this->msp_max_viewports);
		glGetIntegerv(GL_MINOR_VERSION, &this->msp_api_minor_version);
		glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &this->msp_num_compressed_texture_formats);
		glGetIntegerv(GL_NUM_EXTENSIONS, &this->msp_num_extensions);
		glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &this->msp_num_program_binary_formats);
		glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &this->msp_num_shader_binary_formats);
		glGetFloatv(GL_POINT_SIZE_GRANULARITY, &this->msp_point_size_granularity);
		glGetFloatv(GL_POINT_SIZE_RANGE, this->msp_point_size_range.data());
		glGetBooleanv(GL_SHADER_COMPILER, &this->msp_shader_compiler);
		glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, this->msp_smooth_line_width_range.data());
		glGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY, &this->msp_smooth_line_width_granularity);
		glGetIntegerv(GL_SUBPIXEL_BITS, &this->msp_subpixel_bits);
		glGetIntegerv(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, &this->msp_max_vertex_attrib_relative_offset);
		glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &this->msp_max_vertex_attrib_bindings);
		glGetIntegerv(GL_VIEWPORT_BOUNDS_RANGE, this->msp_viewport_bounds_range.data());
		glGetIntegerv(GL_VIEWPORT_INDEX_PROVOKING_VERTEX, &this->msp_viewport_index_provoking_vertex);
		glGetIntegerv(GL_VIEWPORT_SUBPIXEL_BITS, &this->msp_viewport_subpixel_bits);
		glGetIntegerv(GL_MAX_ELEMENT_INDEX, &this->msp_max_element_index);
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &this->msp_max_color_attachments);

		this->msp_compressed_texture_formats.resize(this->msp_num_compressed_texture_formats);
		glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, this->msp_compressed_texture_formats.data());
		this->msp_program_binary_formats.resize(this->msp_num_program_binary_formats);
		glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, this->msp_program_binary_formats.data());
	}
#pragma region APg
#define EVO_OGL_APG(ctype, name, gltfn, glname) \
		ctype Parameters::name() const { ctype v; glGet##gltfn##v(glname, &v); return v; }

#define EVO_OGL_APGi(ctype, name, gltfn, glname) \
		ctype Parameters::name(gl_uint_t i) const { ctype v; glGet##gltfn##i_v(glname, i, &v); return v; }

#define EVO_OGL_APGd(ctype, num, name, gltfn, glname) \
		std::array<ctype, num> Parameters::name() const { std::array<ctype, num> v; glGet##gltfn##v(glname, v.data()); return v; }

#define EVO_OGL_APGdi(ctype, num, name, gltfn, glname) \
		std::array<ctype, num> Parameters::name(gl_uint_t i) const { \
			std::array<ctype, num> v; glGet##gltfn##i_v(glname, i, v.data()); \
			return v; \
		}

	EVO_OGL_APG(gl_int_t, active_texture, Integer, GL_ACTIVE_TEXTURE);
	EVO_OGL_APG(gl_int_t, array_buffer_binding, Integer, GL_ARRAY_BUFFER_BINDING);
	EVO_OGL_APG(gl_boolean_t, blend, Boolean, GL_BLEND);
	EVO_OGL_APGi(gl_boolean_t, blend, Boolean, GL_BLEND);
	EVO_OGL_APGd(gl_float_t, 4, blend_color, Float, GL_BLEND_COLOR);
	EVO_OGL_APG(gl_int_t, blend_dst_alpha, Integer, GL_BLEND_DST_ALPHA);
	EVO_OGL_APG(gl_int_t, blend_dst_rgb, Integer, GL_BLEND_DST_RGB);
	EVO_OGL_APG(gl_int_t, blend_equation_rgb, Integer, GL_BLEND_EQUATION_RGB);
	EVO_OGL_APG(gl_int_t, blend_equation_alpha, Integer, GL_BLEND_EQUATION_ALPHA);
	EVO_OGL_APG(gl_int_t, blend_src_alpha, Integer, GL_BLEND_SRC_ALPHA);
	EVO_OGL_APG(gl_int_t, blend_src_rgb, Integer, GL_BLEND_SRC_RGB);
	EVO_OGL_APGd(gl_float_t, 4, color_clear_value, Float, GL_COLOR_CLEAR_VALUE);
	EVO_OGL_APG(gl_boolean_t, color_logic_op, Boolean, GL_COLOR_LOGIC_OP);
	EVO_OGL_APGd(gl_boolean_t, 4, color_writemask, Boolean, GL_COLOR_WRITEMASK);
	EVO_OGL_APGdi(gl_boolean_t, 4, color_writemask, Boolean, GL_COLOR_WRITEMASK);
	EVO_OGL_APG(gl_int_t, dispatch_indirect_buffer_binding, Integer, GL_DISPATCH_INDIRECT_BUFFER_BINDING);
	EVO_OGL_APG(gl_int_t, debug_group_stack_depth, Integer, GL_DEBUG_GROUP_STACK_DEPTH);
	EVO_OGL_APG(gl_boolean_t, cull_face, Boolean, GL_CULL_FACE);
	EVO_OGL_APG(gl_int_t, cull_face_mode, Integer, GL_CULL_FACE_MODE);
	EVO_OGL_APG(gl_int_t, current_program, Integer, GL_CURRENT_PROGRAM);
	EVO_OGL_APG(gl_double_t, depth_clear_value, Double, GL_DEPTH_CLEAR_VALUE);
	EVO_OGL_APG(gl_int_t, depth_func, Integer, GL_DEPTH_FUNC);
	EVO_OGL_APGd(gl_double_t, 2, depth_range, Double, GL_DEPTH_RANGE);
	EVO_OGL_APG(gl_boolean_t, depth_test, Boolean, GL_DEPTH_TEST);
	EVO_OGL_APG(gl_boolean_t, depth_writemask, Boolean, GL_DEPTH_WRITEMASK);
	EVO_OGL_APG(gl_boolean_t, dither, Boolean, GL_DITHER);
	EVO_OGL_APGi(gl_int_t, draw_buffer, Integer, GL_DRAW_BUFFER);
	EVO_OGL_APG(gl_int_t, draw_framebuffer_binding, Integer, GL_DRAW_FRAMEBUFFER_BINDING);
	EVO_OGL_APG(gl_int_t, read_framebuffer_binding, Integer, GL_READ_FRAMEBUFFER_BINDING);
	EVO_OGL_APG(gl_int_t, element_array_buffer_binding, Integer, GL_ELEMENT_ARRAY_BUFFER_BINDING);
	EVO_OGL_APG(gl_int_t, fragment_shader_derivative_hint, Integer, GL_FRAGMENT_SHADER_DERIVATIVE_HINT);
	EVO_OGL_APG(gl_boolean_t, line_smooth, Boolean, GL_LINE_SMOOTH);
	EVO_OGL_APG(gl_int_t, line_smooth_hint, Integer, GL_LINE_SMOOTH_HINT);
	EVO_OGL_APG(gl_float_t, line_width, Float, GL_LINE_WIDTH);
	EVO_OGL_APG(gl_int_t, logic_op_mode, Integer, GL_LOGIC_OP_MODE);
	EVO_OGL_APG(gl_int_t, pack_alignment, Integer, GL_PACK_ALIGNMENT);
	EVO_OGL_APG(gl_int_t, pack_image_height, Integer, GL_PACK_IMAGE_HEIGHT);
	EVO_OGL_APG(gl_boolean_t, pack_lsb_first, Boolean, GL_PACK_LSB_FIRST);
	EVO_OGL_APG(gl_int_t, pack_row_length, Integer, GL_PACK_ROW_LENGTH);
	EVO_OGL_APG(gl_int_t, pack_skip_images, Integer, GL_PACK_SKIP_IMAGES);
	EVO_OGL_APG(gl_int_t, pack_skip_pixels, Integer, GL_PACK_SKIP_PIXELS);
	EVO_OGL_APG(gl_int_t, pack_skip_rows, Integer, GL_PACK_SKIP_ROWS);
	EVO_OGL_APG(gl_boolean_t, pack_swap_bytes, Boolean, GL_PACK_SWAP_BYTES);
	EVO_OGL_APG(gl_int_t, pixel_pack_buffer_binding, Integer, GL_PIXEL_PACK_BUFFER_BINDING);
	EVO_OGL_APG(gl_int_t, pixel_unpack_buffer_binding, Integer, GL_PIXEL_UNPACK_BUFFER_BINDING);
	EVO_OGL_APG(gl_float_t, point_fade_threshold_size, Float, GL_POINT_FADE_THRESHOLD_SIZE);
	EVO_OGL_APG(gl_int_t, primitive_restart_index, Integer, GL_PRIMITIVE_RESTART_INDEX);
	EVO_OGL_APG(gl_int_t, program_pipeline_binding, Integer, GL_PROGRAM_PIPELINE_BINDING);
	EVO_OGL_APG(gl_boolean_t, program_point_size, Boolean, GL_PROGRAM_POINT_SIZE);
	EVO_OGL_APG(gl_int_t, provoking_vertex, Integer, GL_PROVOKING_VERTEX);
	EVO_OGL_APG(gl_float_t, point_size, Float, GL_POINT_SIZE);
	EVO_OGL_APG(gl_float_t, polygon_offset_factor, Float, GL_POLYGON_OFFSET_FACTOR);
	EVO_OGL_APG(gl_float_t, polygon_offset_units, Float, GL_POLYGON_OFFSET_UNITS);
	EVO_OGL_APG(gl_boolean_t, polygon_offset_fill, Boolean, GL_POLYGON_OFFSET_FILL);
	EVO_OGL_APG(gl_boolean_t, polygon_offset_line, Boolean, GL_POLYGON_OFFSET_LINE);
	EVO_OGL_APG(gl_boolean_t, polygon_offset_point, Boolean, GL_POLYGON_OFFSET_POINT);
	EVO_OGL_APG(gl_boolean_t, polygon_smooth, Boolean, GL_POLYGON_SMOOTH);
	EVO_OGL_APG(gl_int_t, polygon_smooth_hint, Integer, GL_POLYGON_SMOOTH_HINT);
	EVO_OGL_APG(gl_int_t, read_buffer, Integer, GL_READ_BUFFER);
	EVO_OGL_APG(gl_int_t, renderbuffer_binding, Integer, GL_RENDERBUFFER_BINDING);
	EVO_OGL_APG(gl_int_t, sample_buffers, Integer, GL_SAMPLE_BUFFERS);
	EVO_OGL_APG(gl_float_t, sample_coverage_value, Float, GL_SAMPLE_COVERAGE_VALUE);
	EVO_OGL_APG(gl_boolean_t, sample_coverage_invert, Boolean, GL_SAMPLE_COVERAGE_INVERT);
	EVO_OGL_APG(gl_int_t, sampler_binding, Integer, GL_SAMPLER_BINDING);
	EVO_OGL_APG(gl_int_t, samples, Integer, GL_SAMPLES);
	EVO_OGL_APGd(gl_float_t, 4, scissor_box, Float, GL_SCISSOR_BOX);
	EVO_OGL_APG(gl_boolean_t, scissor_test, Boolean, GL_SCISSOR_TEST);
	EVO_OGL_APGi(gl_boolean_t, scissor_test, Boolean, GL_SCISSOR_TEST);
	EVO_OGL_APG(gl_int_t, shader_storage_buffer_offset_alignment, Integer, GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT);
	EVO_OGL_APG(gl_int_t, shader_storage_buffer_binding, Integer, GL_SHADER_STORAGE_BUFFER_BINDING);
	EVO_OGL_APGi(gl_int_t, shader_storage_buffer_binding, Integer, GL_SHADER_STORAGE_BUFFER_BINDING);
	EVO_OGL_APG(gl_int64_t, shader_storage_buffer_start, Integer64, GL_SHADER_STORAGE_BUFFER_START);
	EVO_OGL_APGi(gl_int64_t, shader_storage_buffer_start, Integer64, GL_SHADER_STORAGE_BUFFER_START);
	EVO_OGL_APG(gl_int64_t, shader_storage_buffer_size, Integer64, GL_SHADER_STORAGE_BUFFER_SIZE);
	EVO_OGL_APGi(gl_int64_t, shader_storage_buffer_size, Integer64, GL_SHADER_STORAGE_BUFFER_SIZE);
	EVO_OGL_APG(gl_int_t, stencil_back_fail, Integer, GL_STENCIL_BACK_FAIL);
	EVO_OGL_APG(gl_int_t, stencil_back_func, Integer, GL_STENCIL_BACK_FUNC);
	EVO_OGL_APG(gl_int_t, stencil_back_pass_depth_fail, Integer, GL_STENCIL_BACK_PASS_DEPTH_FAIL);
	EVO_OGL_APG(gl_int_t, stencil_back_pass_depth_pass, Integer, GL_STENCIL_BACK_PASS_DEPTH_PASS);
	EVO_OGL_APG(gl_int_t, stencil_back_ref, Integer, GL_STENCIL_BACK_REF);
	EVO_OGL_APG(gl_int_t, stencil_back_value_mask, Integer, GL_STENCIL_BACK_VALUE_MASK);
	EVO_OGL_APG(gl_int_t, stencil_back_writemask, Integer, GL_STENCIL_BACK_WRITEMASK); 
	EVO_OGL_APG(gl_int_t, stencil_clear_value, Integer, GL_STENCIL_CLEAR_VALUE);
	EVO_OGL_APG(gl_int_t, stencil_fail, Integer, GL_STENCIL_FAIL);
	EVO_OGL_APG(gl_int_t, stencil_func, Integer, GL_STENCIL_FUNC);
	EVO_OGL_APG(gl_int_t, stencil_pass_depth_fail, Integer, GL_STENCIL_PASS_DEPTH_FAIL);
	EVO_OGL_APG(gl_int_t, stencil_pass_depth_pass, Integer, GL_STENCIL_PASS_DEPTH_PASS);
	EVO_OGL_APG(gl_int_t, stencil_ref, Integer, GL_STENCIL_REF);
	EVO_OGL_APG(gl_boolean_t, stencil_test, Boolean, GL_STENCIL_TEST);
	EVO_OGL_APG(gl_int_t, stencil_value_mask, Integer, GL_STENCIL_VALUE_MASK);
	EVO_OGL_APG(gl_int_t, stencil_writemask, Integer, GL_STENCIL_WRITEMASK);
	EVO_OGL_APG(gl_boolean_t, stereo, Boolean, GL_STEREO);
	EVO_OGL_APG(gl_int_t, texture_binding_1_d, Integer, GL_TEXTURE_BINDING_1D);
	EVO_OGL_APG(gl_int_t, texture_binding_1_d_array, Integer, GL_TEXTURE_BINDING_1D_ARRAY);
	EVO_OGL_APG(gl_int_t, texture_binding_2_d, Integer, GL_TEXTURE_BINDING_2D);
	EVO_OGL_APG(gl_int_t, texture_binding_2_d_array, Integer, GL_TEXTURE_BINDING_2D_ARRAY);
	EVO_OGL_APG(gl_int_t, texture_binding_2_d_multisample, Integer, GL_TEXTURE_BINDING_2D_MULTISAMPLE);
	EVO_OGL_APG(gl_int_t, texture_binding_2_d_multisample_array, Integer, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY);
	EVO_OGL_APG(gl_int_t, texture_binding_3_d, Integer, GL_TEXTURE_BINDING_3D);
	EVO_OGL_APG(gl_int_t, texture_binding_buffer, Integer, GL_TEXTURE_BINDING_BUFFER);
	EVO_OGL_APG(gl_int_t, texture_binding_cube_map, Integer, GL_TEXTURE_BINDING_CUBE_MAP);
	EVO_OGL_APG(gl_int_t, texture_binding_rectangle, Integer, GL_TEXTURE_BINDING_RECTANGLE);
	EVO_OGL_APG(gl_int_t, texture_compression_hint, Integer, GL_TEXTURE_COMPRESSION_HINT);
	//EVO_OGL_APG(gl_int_t, texture_binding_buffer, Integer, GL_TEXTURE_BINDING_BUFFER);
	EVO_OGL_APG(gl_int_t, texture_buffer_offset_alignment, Integer, GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT);
	EVO_OGL_APG(gl_int64_t, timestamp, Integer64, GL_TIMESTAMP); 
	EVO_OGL_APG(gl_int_t, transform_feedback_buffer_binding, Integer, GL_TRANSFORM_FEEDBACK_BUFFER_BINDING);
	EVO_OGL_APGi(gl_int_t, transform_feedback_buffer_binding, Integer, GL_TRANSFORM_FEEDBACK_BUFFER_BINDING);
	EVO_OGL_APGi(gl_int64_t, transform_feedback_buffer_start, Integer64, GL_TRANSFORM_FEEDBACK_BUFFER_START);
	EVO_OGL_APGi(gl_int64_t, transform_feedback_buffer_size, Integer64, GL_TRANSFORM_FEEDBACK_BUFFER_SIZE);
	EVO_OGL_APG(gl_int_t, uniform_buffer_binding, Integer, GL_UNIFORM_BUFFER_BINDING);
	EVO_OGL_APGi(gl_int_t, uniform_buffer_binding, Integer, GL_UNIFORM_BUFFER_BINDING);
	EVO_OGL_APG(gl_int_t, uniform_buffer_offset_alignment, Integer, GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT);
	EVO_OGL_APGi(gl_int64_t, uniform_buffer_size, Integer64, GL_UNIFORM_BUFFER_SIZE);
	EVO_OGL_APGi(gl_int64_t, uniform_buffer_start, Integer64, GL_UNIFORM_BUFFER_START);
	EVO_OGL_APG(gl_int_t, unpack_alignment, Integer, GL_UNPACK_ALIGNMENT);
	EVO_OGL_APG(gl_int_t, unpack_image_height, Integer, GL_UNPACK_IMAGE_HEIGHT);
	EVO_OGL_APG(gl_boolean_t, unpack_lsb_first, Boolean, GL_UNPACK_LSB_FIRST);
	EVO_OGL_APG(gl_int_t, unpack_row_length, Integer, GL_UNPACK_ROW_LENGTH);
	EVO_OGL_APG(gl_int_t, unpack_skip_images, Integer, GL_UNPACK_SKIP_IMAGES);
	EVO_OGL_APG(gl_int_t, unpack_skip_pixels, Integer, GL_UNPACK_SKIP_PIXELS);
	EVO_OGL_APG(gl_int_t, unpack_skip_rows, Integer, GL_UNPACK_SKIP_ROWS);
	EVO_OGL_APG(gl_boolean_t, unpack_swap_bytes, Boolean, GL_UNPACK_SWAP_BYTES);
	EVO_OGL_APG(gl_int_t, vertex_array_binding, Integer, GL_VERTEX_ARRAY_BINDING);
	EVO_OGL_APGi(gl_int_t, vertex_binding_divisor, Integer, GL_VERTEX_BINDING_DIVISOR);
	EVO_OGL_APGi(gl_int_t, vertex_binding_offset, Integer, GL_VERTEX_BINDING_OFFSET);
	EVO_OGL_APGi(gl_int_t, vertex_binding_stride, Integer, GL_VERTEX_BINDING_STRIDE);
	EVO_OGL_APGi(gl_int_t, vertex_binding_buffer, Integer, GL_VERTEX_BINDING_BUFFER);
	EVO_OGL_APGd(gl_int_t, 4, viewport, Integer, GL_VIEWPORT);

#undef EVO_OGL_APG
#undef EVO_OGL_APGi
#undef EVO_OGL_APGd
#undef EVO_OGL_APGdi
#pragma endregion
}