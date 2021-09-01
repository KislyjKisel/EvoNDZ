#include "../../../include/EvoNDZ/graphics/opengl/dynamic_vertex_buffer.h"
#include <glad/glad.h>

namespace evo::ogl {
	void DynamicVertexBuffer::write(const void* data, gl_sizeiptr_t size) {
		size_t offset = size;
		size += size;
		if (size > m_capacity) {
			gl_sizeiptr_t oldCapacity = m_capacity;
			m_capacity *= 2;
			glBindBuffer(GL_COPY_READ_BUFFER, m_buffer.m_buffer);
			gl_uint_t newBuffer;
			glCreateBuffers(1, &newBuffer);
			glBindBuffer(GL_COPY_WRITE_BUFFER, newBuffer);
			glBufferData(GL_COPY_WRITE_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
			glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldCapacity);
			glDeleteBuffers(1, &m_buffer.m_buffer);
			m_buffer.m_buffer = newBuffer;
		}
		m_buffer.sub_data(data, size, offset);
	}
}