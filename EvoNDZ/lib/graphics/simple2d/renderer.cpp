#include "../../../include/EvoNDZ/graphics/simple2d/renderer.h"
#include "../../../include/EvoNDZ/graphics/opengl/state.h"

#include <glad/glad.h>

namespace evo::s2d
{
	Renderer::Renderer() : m_transparentCircleBatch(32), m_opaqueCircleBatch(32)
	{
		app::gl()->clear_color().set({ 0.f, 0.f, 0.f, 0.f });
		app::gl()->enable(ogl::Capability::DepthTest());
		app::gl()->disable(ogl::Capability::StencilTest());
		app::gl()->depth_function().set(ogl::DepthFunction::LessEqual());
		app::gl()->blend(0).set(ogl::gl_true);
		app::gl()->blend_function(0).set(ogl::BlendFunction(ogl::BlendFactor::SrcAlpha(), ogl::BlendFactor::OneMinusSrcAlpha()));
	
		glEnable(GL_BLEND);
	}

	void Renderer::render(const Camera2D<float>& c) {
		app::gl()->clear(ogl::BufferBit::Color() | ogl::BufferBit::Depth());
		app::gl()->depth_mask().set(ogl::gl_true);
		m_opaqueLineBatch.render(c.matrix());
		m_opaqueCircleBatch.render(c.matrix());
		m_opaqueTriangleBatch.render(c.matrix());
		m_opaqueRectangleBatch.render(c.matrix());
		app::gl()->depth_mask().reset(ogl::gl_false);
		m_transparentLineBatch.render(c.matrix());
		m_transparentCircleBatch.render(c.matrix());
		m_transparentTriangleBatch.render(c.matrix());
		m_transparentRectangleBatch.render(c.matrix());
		app::gl()->depth_mask().revert();
	}
}