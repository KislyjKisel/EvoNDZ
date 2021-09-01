#include "../../../include/EvoNDZ/graphics/opengl/texture2d.h"
#include <glad/glad.h>

namespace evo::ogl {
	Texture2D::Texture2D(
		gl_sizei_t width, gl_sizei_t height, gl_enum_t internalFormat, gl_int_t minFilter, gl_int_t magFilter, gl_int_t wraps, gl_int_t wrapt
	) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
		glTextureStorage2D(m_texture, 1, internalFormat, width, height);
		glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, minFilter);
		glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, magFilter);
		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, wraps);
		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, wrapt);
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_texture);
	}

	void Texture2D::set_border_color(evo::Color4f borderColor) {
		glTextureParameterfv(m_texture, GL_TEXTURE_BORDER_COLOR, (float*)&borderColor);
	}

	void Texture2D::sub_image(gl_int_t xoffset, gl_int_t yoffset, gl_sizei_t width, gl_sizei_t height, gl_enum_t format, gl_enum_t type, const void* pixels) {
		glTextureSubImage2D(m_texture, 0, xoffset, yoffset, width, height, format, type, pixels);
		//glGenerateTextureMipmap(m_texture);
	}

	Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
	{
		if (this != &other) {
			glDeleteTextures(1, &m_texture);
			m_texture = other.m_texture;
			other.m_texture = 0;
		}
		return *this;
	}

	/*Texture2D::Texture2D(const dgl::data::Texture2D& tex) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
		glTextureStorage2D(m_texture, 1, GL_RGB8, tex.width(), tex.height());
		glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureSubImage2D(m_texture, 0, 0, 0, tex.width(), tex.height(), GL_BGRA, GL_UNSIGNED_BYTE, tex.data());
	}*/

}