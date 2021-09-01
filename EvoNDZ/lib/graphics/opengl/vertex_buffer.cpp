#include "../../../include/EvoNDZ/graphics/opengl/vertex_buffer.h"
#include "../../../include/EvoNDZ/graphics/opengl/dynamic_vertex_buffer.h"
#include <glad/glad.h>

namespace evo::ogl
{
	VertexBuffer::VertexBuffer() {
		glCreateBuffers(1, &m_buffer);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_buffer);
	}

	void VertexBuffer::data(const void* data, gl_sizeiptr_t size,  BufferUsage usage) {
		glNamedBufferData(m_buffer, size, data, usage.value());
	}

	void VertexBuffer::sub_data(const void* data, gl_sizeiptr_t size, gl_intptr_t offset) {
		glNamedBufferSubData(m_buffer, offset, size, data);
	}

	void VertexBuffer::storage(const void* data, gl_sizeiptr_t size, StorageFlags flags) {
		glNamedBufferStorage(m_buffer, size, data, flags.value());
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		if (this != &other) {
			glDeleteBuffers(1, &m_buffer);
			m_buffer = other.m_buffer;
			other.m_buffer = 0;
		}
		return *this;
	}

	VertexBuffer::VertexBuffer(DynamicVertexBuffer&& dvb) noexcept {
		glBindBuffer(GL_COPY_READ_BUFFER, dvb.m_buffer.m_buffer);
		glCreateBuffers(1, &m_buffer);
		glBindBuffer(GL_COPY_WRITE_BUFFER, m_buffer);
		glBufferData(GL_COPY_WRITE_BUFFER, dvb.size(), nullptr, GL_STATIC_DRAW);
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, dvb.size());
		glDeleteBuffers(1, &dvb.m_buffer.m_buffer);
		dvb.m_buffer.m_buffer = 0;
	}
}