#include "../../../include/EvoNDZ/graphics/opengl/render_target.h"
#include <cassert>
#include <glad/glad.h>

namespace evo::ogl {
	RenderTarget::RenderTarget(uint32_t width, uint32_t height) : m_width(width), m_height(height) {
		glCreateFramebuffers(1, &m_framebuffer);
	}

	bool RenderTarget::is_complete() const {
		return glCheckNamedFramebufferStatus(m_framebuffer, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}

	gl_enum_t RenderTarget::status() const {
		return glCheckNamedFramebufferStatus(m_framebuffer, GL_FRAMEBUFFER);
	}

	RenderTarget::~RenderTarget() {
		for (size_t i = 0; i < MaxColorAttachments; ++i) {
			if (m_colorAttachments[i].name != gl_invalid) {
				if (m_colorAttachments[i].texture) {
					glDeleteTextures(1, &m_colorAttachments[i].name);
				}
				else {
					glDeleteRenderbuffers(1, &m_colorAttachments[i].name);
				}
			}
		}
		if (m_depthStencilAttachment.isSeparate) {
			if (m_depthStencilAttachment.separated.depth!= gl_invalid) {
				if (m_depthStencilAttachment.separated.textureDepth) {
					glDeleteTextures(1, &m_depthStencilAttachment.separated.depth);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.depth);
				}
			}
			if (m_depthStencilAttachment.separated.stencil!= gl_invalid) {
				if (m_depthStencilAttachment.separated.textureStencil) {
					glDeleteTextures(1, &m_depthStencilAttachment.separated.stencil);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.stencil);
				}
			}
		}
		else {
			if (m_depthStencilAttachment.combined.depthStencil!= gl_invalid) {
				if (m_depthStencilAttachment.combined.textureDepthStencil) {
					glDeleteTextures(1, &m_depthStencilAttachment.combined.depthStencil);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.combined.depthStencil);
				}
			}
		}
		glDeleteFramebuffers(1, &m_framebuffer);
		//delete[] m_colorAttachments;
	}

	void RenderTarget::Bind(RenderTarget* rt) {
		glBindFramebuffer(GL_FRAMEBUFFER, rt->m_framebuffer);
	}

	void RenderTarget::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderTarget::attach_texture(gl_uint_t* texture, gl_enum_t format, gl_enum_t attachment, gl_int_t minFilter, gl_int_t magFilter) {
		glCreateTextures(GL_TEXTURE_2D, 1, texture);
		glTextureStorage2D(*texture, 1, format, m_width, m_height);
		glTextureParameteri(*texture, GL_TEXTURE_MIN_FILTER, minFilter);
		glTextureParameteri(*texture, GL_TEXTURE_MAG_FILTER, magFilter);
		glNamedFramebufferTexture(m_framebuffer, attachment, *texture, 0);
	}

	void RenderTarget::attach_renderbuffer(gl_uint_t* renderbuffer, gl_enum_t format, gl_enum_t attachment) {
		glCreateRenderbuffers(1, renderbuffer);
		glNamedRenderbufferStorage(*renderbuffer, format, m_width, m_height);
		glNamedFramebufferRenderbuffer(m_framebuffer, attachment, GL_RENDERBUFFER, *renderbuffer);
	}

	gl_enum_t RenderTarget::ColorAttachmentByIndex(gl_uint_t index) {
		return GL_COLOR_ATTACHMENT0 + index;
	}

	void RenderTarget::attach_color_texture(TextureFormat format, gl_uint_t attachmentIndex) {
#ifndef NDEBUG
		//todo: proper error handling
		assert(attachmentIndex < MaxColorAttachments && "Invalid Attachment Index");

		assert(format.color() && format.sized());
#endif

		if (m_colorAttachments[attachmentIndex].name != gl_invalid) {
			if (m_colorAttachments[attachmentIndex].texture) {
				glDeleteTextures(1, &m_colorAttachments[attachmentIndex].name);
			}
			else {
				glDeleteRenderbuffers(1, &m_colorAttachments[attachmentIndex].name);
			}
		}
		m_colorAttachments[attachmentIndex].texture = true;
		attach_texture(&m_colorAttachments[attachmentIndex].name, format.index(), ColorAttachmentByIndex(attachmentIndex), GL_LINEAR, GL_LINEAR);
	}
	void RenderTarget::attach_color_renderbuffer(TextureFormat format, gl_uint_t attachmentIndex) {
#ifndef NDEBUG
		//todo: proper error handling
		assert(attachmentIndex < MaxColorAttachments && "Invalid Attachment Index");

		assert(format.color() && !format.sized());
#endif
		if (m_colorAttachments[attachmentIndex].name != gl_invalid) {
			if (m_colorAttachments[attachmentIndex].texture) {
				glDeleteTextures(1, &m_colorAttachments[attachmentIndex].name);
			}
			else {
				glDeleteRenderbuffers(1, &m_colorAttachments[attachmentIndex].name);
			}
		}
		m_colorAttachments[attachmentIndex].texture = false;
		attach_renderbuffer(&m_colorAttachments[attachmentIndex].name, format.index(), ColorAttachmentByIndex(attachmentIndex));
	}

	void RenderTarget::attach_depth_texture(TextureFormat format) {
#ifndef NDEBUG
		assert(format.depth() && format.sized());
#endif

		if (m_depthStencilAttachment.isSeparate) {
			if (m_depthStencilAttachment.separated.depth!= gl_invalid) {
				if (m_depthStencilAttachment.separated.textureDepth) {
					glDeleteTextures(1, &m_depthStencilAttachment.separated.depth);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.depth);
				}
			}
		}
		else {
			if (m_depthStencilAttachment.combined.depthStencil!= gl_invalid) {
				if (m_depthStencilAttachment.combined.textureDepthStencil) {
					glNamedFramebufferTexture(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
					glDeleteTextures(1, &m_depthStencilAttachment.combined.depthStencil);
				}
				else {
					glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.combined.depthStencil);
				}
			}
			m_depthStencilAttachment.isSeparate = true;
			m_depthStencilAttachment.separated.stencil= gl_invalid;
		}
		m_depthStencilAttachment.separated.textureDepth = true;
		attach_texture(&m_depthStencilAttachment.separated.depth, format.index(), GL_DEPTH_ATTACHMENT, GL_LINEAR, GL_LINEAR);
	}

	void RenderTarget::attach_depth_renderbuffer(TextureFormat format) {
#ifndef NDEBUG
		assert(format.depth() && !format.sized());
#endif

		if (m_depthStencilAttachment.isSeparate) {
			if (m_depthStencilAttachment.separated.depth!= gl_invalid) {
				if (m_depthStencilAttachment.separated.textureDepth) {
					glDeleteTextures(1, &m_depthStencilAttachment.separated.depth);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.depth);
				}
			}
		}
		else {
			if (m_depthStencilAttachment.combined.depthStencil!= gl_invalid) {
				if (m_depthStencilAttachment.combined.textureDepthStencil) {
					glNamedFramebufferTexture(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
					glDeleteTextures(1, &m_depthStencilAttachment.combined.depthStencil);
				}
				else {
					glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.combined.depthStencil);
				}
			}
			m_depthStencilAttachment.isSeparate = true;
			m_depthStencilAttachment.separated.stencil= gl_invalid;

		}
		m_depthStencilAttachment.separated.textureDepth = false;
		attach_renderbuffer(&m_depthStencilAttachment.separated.depth, format.index(), GL_DEPTH_ATTACHMENT);
	}

	void RenderTarget::attach_stencil_texture(TextureFormat format) {
#ifndef NDEBUG
		assert(format.stencil() && format.sized());
#endif

		if (m_depthStencilAttachment.isSeparate) {
			if (m_depthStencilAttachment.separated.stencil!= gl_invalid) {
				if (m_depthStencilAttachment.separated.textureStencil) {
					glDeleteTextures(1, &m_depthStencilAttachment.separated.stencil);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.stencil);
				}
			}
		}
		else {
			if (m_depthStencilAttachment.combined.depthStencil!= gl_invalid) {
				if (m_depthStencilAttachment.combined.textureDepthStencil) {
					glNamedFramebufferTexture(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
					glDeleteTextures(1, &m_depthStencilAttachment.combined.depthStencil);
				}
				else {
					glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.combined.depthStencil);
				}
			}
			m_depthStencilAttachment.isSeparate = true;
			m_depthStencilAttachment.separated.depth= gl_invalid;
		}
		m_depthStencilAttachment.separated.textureStencil = true;
		attach_texture(&m_depthStencilAttachment.separated.stencil, format.index(), GL_STENCIL_ATTACHMENT, GL_LINEAR, GL_LINEAR);
	}

	void RenderTarget::attach_stencil_renderbuffer(TextureFormat format) {
#ifndef NDEBUG
		assert(format.stencil() && !format.sized());
#endif

		if (m_depthStencilAttachment.isSeparate) {
			if (m_depthStencilAttachment.separated.stencil!= gl_invalid) {
				if (m_depthStencilAttachment.separated.textureStencil) {
					glDeleteTextures(1, &m_depthStencilAttachment.separated.stencil);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.stencil);
				}
			}
		}
		else {
			if (m_depthStencilAttachment.combined.depthStencil!= gl_invalid) {
				if (m_depthStencilAttachment.combined.textureDepthStencil) {
					glNamedFramebufferTexture(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
					glDeleteTextures(1, &m_depthStencilAttachment.combined.depthStencil);
				}
				else {
					glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.combined.depthStencil);
				}
			}
			m_depthStencilAttachment.isSeparate = true;
			m_depthStencilAttachment.separated.depth= gl_invalid;
		}
		m_depthStencilAttachment.separated.textureStencil = false;
		attach_renderbuffer(&m_depthStencilAttachment.separated.stencil, format.index(), GL_STENCIL_ATTACHMENT);
	}

	void RenderTarget::attach_depth_stencil_texture(TextureFormat format) {
#ifndef NDEBUG
		assert(format.depth() && format.stencil());
#endif

		if (m_depthStencilAttachment.isSeparate) {
			if (m_depthStencilAttachment.separated.depth != gl_invalid) {
				if (m_depthStencilAttachment.separated.textureDepth) {
					glNamedFramebufferTexture(m_framebuffer, GL_DEPTH_ATTACHMENT, 0, 0);
					glDeleteTextures(1, &m_depthStencilAttachment.separated.depth);
				}
				else {
					glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_ATTACHMENT, 0, 0);
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.depth);
				}
			}
			if (m_depthStencilAttachment.separated.stencil!= gl_invalid) {
				if (m_depthStencilAttachment.separated.textureStencil) {
					glNamedFramebufferTexture(m_framebuffer, GL_STENCIL_ATTACHMENT, 0, 0);
					glDeleteTextures(1, &m_depthStencilAttachment.separated.stencil);
				}
				else {
					glNamedFramebufferRenderbuffer(m_framebuffer, GL_STENCIL_ATTACHMENT, 0, 0);
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.stencil);
				}
			}
			m_depthStencilAttachment.isSeparate = false;
		}
		else {
			if (m_depthStencilAttachment.combined.depthStencil!= gl_invalid) {
				if (m_depthStencilAttachment.combined.textureDepthStencil) {
					glDeleteTextures(1, &m_depthStencilAttachment.combined.depthStencil);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.combined.depthStencil);
				}
			}
		}
		m_depthStencilAttachment.combined.textureDepthStencil = true;
		attach_texture(&m_depthStencilAttachment.combined.depthStencil, format.index(), GL_DEPTH_STENCIL_ATTACHMENT, GL_LINEAR, GL_LINEAR);
	}

	void RenderTarget::attach_depth_stencil_renderbuffer(TextureFormat format) {
#ifndef NDEBUG
		assert(format.depth() && format.stencil() && !format.sized());
#endif

		if (m_depthStencilAttachment.isSeparate) {
			if (m_depthStencilAttachment.separated.depth != gl_invalid) {
				if (m_depthStencilAttachment.separated.textureDepth) {
					glNamedFramebufferTexture(m_framebuffer, GL_DEPTH_ATTACHMENT, 0, 0);
					glDeleteTextures(1, &m_depthStencilAttachment.separated.depth);
				}
				else {
					glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_ATTACHMENT, 0, 0);
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.depth);
				}
			}
			if (m_depthStencilAttachment.separated.stencil!= gl_invalid) {
				if (m_depthStencilAttachment.separated.textureStencil) {
					glNamedFramebufferTexture(m_framebuffer, GL_STENCIL_ATTACHMENT, 0, 0);
					glDeleteTextures(1, &m_depthStencilAttachment.separated.stencil);
				}
				else {
					glNamedFramebufferRenderbuffer(m_framebuffer, GL_STENCIL_ATTACHMENT, 0, 0);
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.separated.stencil);
				}
			}
			m_depthStencilAttachment.isSeparate = false;
		}
		else {
			if (m_depthStencilAttachment.combined.depthStencil!= gl_invalid) {
				if (m_depthStencilAttachment.combined.textureDepthStencil) {
					glDeleteTextures(1, &m_depthStencilAttachment.combined.depthStencil);
				}
				else {
					glDeleteRenderbuffers(1, &m_depthStencilAttachment.combined.depthStencil);
				}
			}
		}
		m_depthStencilAttachment.combined.textureDepthStencil = false;
		attach_renderbuffer(&m_depthStencilAttachment.combined.depthStencil, format.index(), GL_DEPTH_STENCIL_ATTACHMENT);
	}

	gl_uint_t RenderTarget::color_texture(gl_uint_t attachmentIndex) {
		//todo: proper error handling
		if (attachmentIndex >= MaxColorAttachments || attachmentIndex < 0
			|| m_colorAttachments[attachmentIndex].name == gl_invalid || !m_colorAttachments[attachmentIndex].texture) {

			assert(false && "Invalid Attachment Index");
			return gl_invalid;
		}

		return m_colorAttachments[attachmentIndex].name;
	}

	gl_uint_t RenderTarget::color_renderbuffer(gl_uint_t attachmentIndex) {
		//todo: proper error handling
		if (attachmentIndex >= MaxColorAttachments || attachmentIndex < 0
			|| m_colorAttachments[attachmentIndex].name == gl_invalid || m_colorAttachments[attachmentIndex].texture) {

			assert(false && "Invalid Attachment Index");
			return gl_invalid;
		}

		return m_colorAttachments[attachmentIndex].name;
	}

	gl_uint_t RenderTarget::move_color_texture(gl_uint_t attachmentIndex) {
		//todo: proper error handling
		if (attachmentIndex >= MaxColorAttachments || attachmentIndex < 0
			|| m_colorAttachments[attachmentIndex].name == gl_invalid || !m_colorAttachments[attachmentIndex].texture) {

			assert(false && "Invalid Attachment Index");
			return gl_invalid;
		}

		gl_uint_t textureName = m_colorAttachments[attachmentIndex].name;
		glNamedFramebufferTexture(m_framebuffer, ColorAttachmentByIndex(attachmentIndex), 0, 0);
		m_colorAttachments[attachmentIndex].name = gl_invalid;
		return textureName;
	}

	gl_uint_t RenderTarget::move_color_renderbuffer(gl_uint_t attachmentIndex) {
		//todo: proper error handling
		if (attachmentIndex >= MaxColorAttachments || attachmentIndex < 0
			|| m_colorAttachments[attachmentIndex].name == gl_invalid || m_colorAttachments[attachmentIndex].texture) {

			assert(false && "Invalid Attachment Index");
			return gl_invalid;
		}

		gl_uint_t renderbufferName = m_colorAttachments[attachmentIndex].name;
		glNamedFramebufferRenderbuffer(m_framebuffer, ColorAttachmentByIndex(attachmentIndex), 0, 0);
		m_colorAttachments[attachmentIndex].name = gl_invalid;
		return renderbufferName;
	}

	gl_uint_t RenderTarget::depth_texture() {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.separated.textureDepth
			|| m_depthStencilAttachment.separated.depth == gl_invalid) {

			assert(false && "No depth texture attached.");
			return gl_invalid;
		}

		return m_depthStencilAttachment.separated.depth;
	}

	gl_uint_t RenderTarget::depth_renderbuffer() {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || m_depthStencilAttachment.separated.textureDepth
			|| m_depthStencilAttachment.separated.depth == gl_invalid) {

			assert(false && "No depth renderbuffer attached.");
			return gl_invalid;
		}

		return m_depthStencilAttachment.separated.depth;
	}

	gl_uint_t RenderTarget::move_depth_texture() {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.separated.textureDepth
			|| m_depthStencilAttachment.separated.depth == gl_invalid) {

			assert(false && "No depth texture attached.");
			return gl_invalid;
		}

		gl_uint_t textureName = m_depthStencilAttachment.separated.depth;
		glNamedFramebufferTexture(m_framebuffer, GL_DEPTH_ATTACHMENT, 0, 0);
		m_depthStencilAttachment.separated.depth = gl_invalid;
		return textureName;
	}

	gl_uint_t RenderTarget::move_depth_renderbuffer() {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || m_depthStencilAttachment.separated.textureDepth
			|| m_depthStencilAttachment.separated.depth == gl_invalid) {

			assert(false && "No depth renderbuffer attached.");
			return gl_invalid;
		}

		gl_uint_t renderbufferName = m_depthStencilAttachment.separated.depth;
		glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_ATTACHMENT, 0, 0);
		m_depthStencilAttachment.separated.depth = gl_invalid;
		return renderbufferName;
	}

	gl_uint_t RenderTarget::stencil_texture() {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.separated.textureStencil
			|| m_depthStencilAttachment.separated.stencil== gl_invalid) {

			assert(false && "No stencil texture attached.");
			return gl_invalid;
		}

		return m_depthStencilAttachment.separated.stencil;
	}

	gl_uint_t RenderTarget::stencil_renderbuffer() {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || m_depthStencilAttachment.separated.textureStencil
			|| m_depthStencilAttachment.separated.stencil== gl_invalid) {

			assert(false && "No stencil renderbuffer attached.");
			return gl_invalid;
		}

		return m_depthStencilAttachment.separated.stencil;
	}

	gl_uint_t RenderTarget::move_stencil_texture() {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.separated.textureStencil
			|| m_depthStencilAttachment.separated.stencil== gl_invalid) {

			assert(false && "No stencil texture attached.");
			return gl_invalid;
		}

		gl_uint_t textureName = m_depthStencilAttachment.separated.stencil;
		glNamedFramebufferTexture(m_framebuffer, GL_STENCIL_ATTACHMENT, 0, 0);
		m_depthStencilAttachment.separated.stencil= gl_invalid;
		return textureName;
	}

	gl_uint_t RenderTarget::move_stencil_renderbuffer() {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || m_depthStencilAttachment.separated.textureStencil
			|| m_depthStencilAttachment.separated.stencil== gl_invalid) {

			assert(false && "No stencil renderbuffer attached.");
			return gl_invalid;
		}

		gl_uint_t renderbufferName = m_depthStencilAttachment.separated.stencil;
		glNamedFramebufferRenderbuffer(m_framebuffer, GL_STENCIL_ATTACHMENT, 0, 0);
		m_depthStencilAttachment.separated.stencil= gl_invalid;
		return renderbufferName;
	}

	gl_uint_t RenderTarget::depth_stencil_texture() {
		//todo: proper error handling
		if (m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.combined.textureDepthStencil
			|| m_depthStencilAttachment.combined.depthStencil== gl_invalid) {

			assert(false && "No depth/stencil texture attached.");
			return gl_invalid;
		}

		return m_depthStencilAttachment.combined.depthStencil;
	}

	gl_uint_t RenderTarget::depth_stencil_renderbuffer() {
		//todo: proper error handling
		if (m_depthStencilAttachment.isSeparate || m_depthStencilAttachment.combined.textureDepthStencil
			|| m_depthStencilAttachment.combined.depthStencil== gl_invalid) {

			assert(false && "No depth/stencil renderbuffer attached.");
			return gl_invalid;
		}

		return m_depthStencilAttachment.combined.depthStencil;
	}

	gl_uint_t RenderTarget::move_depth_stencil_texture() {
		//todo: proper error handling
		if (m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.combined.textureDepthStencil
			|| m_depthStencilAttachment.combined.depthStencil== gl_invalid) {

			assert(false && "No depth/stencil texture attached.");
			return gl_invalid;
		}

		gl_uint_t textureName = m_depthStencilAttachment.combined.depthStencil;
		glNamedFramebufferTexture(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
		m_depthStencilAttachment.combined.depthStencil= gl_invalid;
		return textureName;
	}

	gl_uint_t RenderTarget::move_depth_stencil_renderbuffer() {
		//todo: proper error handling
		if (m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.combined.textureDepthStencil
			|| m_depthStencilAttachment.combined.depthStencil== gl_invalid) {

			assert(false && "No depth/stencil renderbuffer attached.");
			return gl_invalid;
		}

		gl_uint_t renderbufferName = m_depthStencilAttachment.combined.depthStencil;
		glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0);
		m_depthStencilAttachment.combined.depthStencil= gl_invalid;
		return renderbufferName;
	}

	void RenderTarget::copy_depth_texture_to(gl_uint_t dest) {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.separated.textureDepth
			|| m_depthStencilAttachment.separated.depth == gl_invalid) {

			assert(false && "No depth texture attached.");
		}

		glCopyImageSubData(m_depthStencilAttachment.separated.depth, 
			GL_TEXTURE_2D, 0, 0, 0, 0, dest, GL_TEXTURE_2D, 0, 0, 0, 0, m_width, m_height, 1);
	}

	void RenderTarget::copy_stencil_texture_to(gl_uint_t dest) {
		//todo: proper error handling
		if (!m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.separated.textureStencil
			|| m_depthStencilAttachment.separated.stencil == gl_invalid) {

			assert(false && "No stencil texture attached.");
		}

		glCopyImageSubData(m_depthStencilAttachment.separated.stencil,
			GL_TEXTURE_2D, 0, 0, 0, 0, dest, GL_TEXTURE_2D, 0, 0, 0, 0, m_width, m_height, 1);
	}

	void RenderTarget::copy_depth_stencil_texture_to(gl_uint_t dest) {
		//todo: proper error handling
		if (m_depthStencilAttachment.isSeparate || !m_depthStencilAttachment.combined.textureDepthStencil
			|| m_depthStencilAttachment.combined.depthStencil == gl_invalid) {

			assert(false && "No depth/stencil texture attached.");
		}

		glCopyImageSubData(m_depthStencilAttachment.combined.depthStencil,
			GL_TEXTURE_2D, 0, 0, 0, 0, dest, GL_TEXTURE_2D, 0, 0, 0, 0, m_width, m_height, 1);
	}
}