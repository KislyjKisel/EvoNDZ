#include "../../../include/EvoNDZ/graphics/opengl/index_type.h"
#include <glad/glad.h>

namespace evo::ogl
{
	template<Index T>
	gl_enum_t index_type_id() noexcept {
		if constexpr (std::is_same_v<T, uint8_t>) return GL_UNSIGNED_BYTE;
		if constexpr (std::is_same_v<T, uint16_t>) return GL_UNSIGNED_SHORT;
		if constexpr (std::is_same_v<T, uint32_t>) return GL_UNSIGNED_INT;
		return 0;
	}

	template gl_enum_t index_type_id<uint8_t>();
	template gl_enum_t index_type_id<uint16_t>();
	template gl_enum_t index_type_id<uint32_t>();
}