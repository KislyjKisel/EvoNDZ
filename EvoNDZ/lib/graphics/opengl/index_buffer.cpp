#include "../../../include/EvoNDZ/graphics/opengl/index_buffer.h"
#include <glad\glad.h>

namespace evo::ogl
{
	IndexBuffer::IndexBuffer() {
		glCreateBuffers(1, &m_buffer);
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_buffer);
	}

	template<Index T>
	void IndexBuffer::data(const T* data, size_t count, BufferUsage usage) {
		glNamedBufferData(m_buffer, count * sizeof(T), data, usage.value());
	}

	template<Index T>
	void IndexBuffer::sub_data(const T* indices, size_t count, gl_intptr_t offset) {
		glNamedBufferSubData(m_buffer, offset, count * sizeof(T), indices);
	}

	template<Index T>
	void IndexBuffer::storage(const T* indices, size_t count, StorageFlags flags) {
		glNamedBufferStorage(m_buffer, count * sizeof(T), indices, flags.value());
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other) {
			glDeleteBuffers(1, &m_buffer);
			m_buffer = other.m_buffer;
			other.m_buffer = 0;
		}
		return *this;
	}

	template void IndexBuffer::data<uint8_t>(const uint8_t*, size_t, BufferUsage);
	template void IndexBuffer::data<uint16_t>(const uint16_t*, size_t, BufferUsage);
	template void IndexBuffer::data<uint32_t>(const uint32_t*, size_t, BufferUsage);

	template void IndexBuffer::sub_data<uint8_t>(const uint8_t*, size_t, gl_intptr_t);
	template void IndexBuffer::sub_data<uint16_t>(const uint16_t*, size_t, gl_intptr_t);
	template void IndexBuffer::sub_data<uint32_t>(const uint32_t*, size_t, gl_intptr_t);

	template void IndexBuffer::storage<uint8_t>(const uint8_t*, size_t, StorageFlags);
	template void IndexBuffer::storage<uint16_t>(const uint16_t*, size_t, StorageFlags);
	template void IndexBuffer::storage<uint32_t>(const uint32_t*, size_t, StorageFlags);
}