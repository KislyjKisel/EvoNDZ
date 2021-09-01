#include "../../../include/EvoNDZ/graphics/opengl/vertex_array.h"
#include <glad\glad.h>

namespace evo::ogl {
	VertexArray::VertexArray() {
		glCreateVertexArrays(1, &m_vao);
	}
	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_vao);
	}
	void VertexArray::enable_attribute(gl_uint_t index) {
		glEnableVertexArrayAttrib(m_vao, index);
	}
	void VertexArray::disable_attribute(gl_uint_t index) {
		glDisableVertexArrayAttrib(m_vao, index);
	}
	void VertexArray::generate() {
		glDeleteVertexArrays(1, &m_vao);
		glCreateVertexArrays(1, &m_vao);
	}
	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		if (this != &other) {
			glDeleteVertexArrays(1, &m_vao);
			m_vao = other.m_vao;
			other.m_vao = 0;
		}
		return *this;
	}
}