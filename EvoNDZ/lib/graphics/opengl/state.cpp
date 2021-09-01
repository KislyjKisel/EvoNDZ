#include "../../../include/EvoNDZ/graphics/opengl/state.h"
#include <glad/glad.h>
#include "../../../include/EvoNDZ/graphics/opengl/texture2d.h"
#include "../../../include/EvoNDZ/graphics/opengl/vertex_array.h"
#include "../../../include/EvoNDZ/graphics/opengl/vertex_buffer.h"
#include "../../../include/EvoNDZ/graphics/opengl/index_buffer.h"
#include "../../../include/EvoNDZ/graphics/opengl/technique.h"
#include "../../../include/EvoNDZ/graphics/opengl/parameters.h"

namespace evo::ogl 
{
	State::State() {
		for (const auto& cap : Capability::Capabilities()) {
			m_capabilities[cap.index()].push_back(m_parameters.is_enabled(cap));
		}

		m_scissorTest = std::make_unique<Storage<gl_boolean_t, ScissorTestFunc>[]>(m_parameters.max_draw_buffers());
		m_blend = std::make_unique<Storage<gl_boolean_t, BlendFunc>[]>(m_parameters.max_draw_buffers());
		m_blendFunction = std::make_unique<Storage<BlendFunction, BlendFunctionFunc>[]>(m_parameters.max_draw_buffers());
		m_blendEquation = std::make_unique<Storage<BlendEquationSeparate, BlendEquationFunc>[]>(m_parameters.max_draw_buffers());
		m_colorWritemask = std::make_unique<Storage<ColorMask, ColorMaskFunc>[]>(m_parameters.max_draw_buffers());
		for (gl_int_t i = 0; i < m_parameters.max_draw_buffers(); ++i) {
			m_scissorTest[i].initialize(m_parameters.scissor_test(i), i);
			m_blend[i].initialize(m_parameters.blend(i), i);
			m_blendFunction[i].initialize({
				BlendFactor(m_parameters.blend_src_rgb()),
				BlendFactor(m_parameters.blend_src_alpha()),
				BlendFactor(m_parameters.blend_dst_rgb()),
				BlendFactor(m_parameters.blend_dst_alpha())
			}, i);
			m_blendEquation[i].initialize(
				BlendEquationSeparate(m_parameters.blend_equation_rgb(), m_parameters.blend_equation_alpha()), i);
			const auto colorMask = m_parameters.color_writemask(i);
			m_colorWritemask[i].initialize(ColorMask(colorMask[0], colorMask[1], colorMask[2], colorMask[3]), i);
		}
		
		m_depthFunction.initialize(DepthFunction(m_parameters.depth_func())); 
		m_logicalOperation.initialize(LogicalPixelOperation(m_parameters.logic_op_mode()));
		m_depthWritemask.initialize(m_parameters.depth_writemask());
		m_clearDepth.initialize(m_parameters.depth_clear_value());

		const auto blendColor = m_parameters.blend_color();
		m_blendColor.initialize(Color4(blendColor[0], blendColor[1], blendColor[2], blendColor[3]));

		const auto clearColor = m_parameters.color_clear_value();
		m_clearColor.initialize(Color4(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));

		m_texture = std::make_unique<std::vector<gl_uint_t>[]>(m_parameters.max_combined_texture_image_units());
		for (size_t i = 0; i < m_parameters.max_combined_texture_image_units(); ++i) {
			m_texture[i].push_back(0);
		}

		m_renderTarget.push_back(nullptr);
		m_vertexArray.push_back(0);
		m_vertexBuffer.push_back(0);
		m_indexBuffer.push_back(0);
		m_technique.push_back(0);
	}
	State::~State() {
		//todo: ? unbind all
	}

#pragma region Storage set functions
	void State::BlendEquationFunc::operator()(BlendEquationSeparate beqs) const {
		glBlendEquationSeparatei(m_buf, beqs.rgb.value(), beqs.alpha.value());
	}
	void State::ScissorTestFunc::operator()(gl_boolean_t v) const {
		v == gl_true ? glEnablei(GL_SCISSOR_TEST, m_buf) : glDisablei(GL_SCISSOR_TEST, m_buf);
	}
	void State::BlendFunc::operator()(gl_boolean_t v) const {
		v == gl_true ? glEnablei(GL_BLEND, m_buf) : glDisablei(GL_BLEND, m_buf);
	}
	void State::BlendFunctionFunc::operator()(BlendFunction v) const {
		glBlendFuncSeparatei(m_buf, v.srcRGB.value(), v.dstRGB.value(), v.srcA.value(), v.dstA.value());
	}
	void State::ColorMaskFunc::operator()(ColorMask m) const {
		glColorMaski(m_buf, m.r, m.g, m.b, m.a);
	}
	void State::BlendColorFunc::operator()(const Color4f& c) const {
		glBlendColor(c.r, c.g, c.b, c.a);
	}
	void State::ClearColorFunc::operator()(const Color4f& c) const {
		glClearColor(c.r, c.g, c.b, c.a);
	}
	void State::ClearDepthFunc::operator()(gl_double_t v) const {
		glClearDepth(v);
	}
	void State::DepthMaskFunc::operator()(gl_boolean_t v) const {
		glDepthMask(v);
	}
	void State::DepthFunctionFunc::operator()(DepthFunction f) const {
		glDepthFunc(f.value());
	}
	void State::LogicOpFunc::operator()(LogicalPixelOperation op) const {
		glLogicOp(op.value());
	}
#pragma endregion

	void State::clear(BufferBit bit) { 
		glClear(bit.value());
	}

	void State::bind_texture(const ::evo::ogl::Texture2D& texture, int textureUnitIndex) {
		m_texture[textureUnitIndex].push_back(texture.m_texture);
		glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
		glBindTexture(GL_TEXTURE_2D, texture.m_texture);
	}
	void State::unbind_texture(int textureUnitIndex) {
		m_texture[textureUnitIndex].push_back(0);
		glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void State::rebind_texture(const evo::ogl::Texture2D& texture, int textureUnitIndex) {
		glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
		glBindTexture(GL_TEXTURE_2D, texture.m_texture);
		m_texture[textureUnitIndex][m_texture[textureUnitIndex].size() - 1] = texture.m_texture;
	}
	void State::revert_texture(int textureUnitIndex) {
		m_texture[textureUnitIndex].pop_back();
		glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
		if (m_texture[textureUnitIndex].empty()) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		glBindTexture(GL_TEXTURE_2D, m_texture[textureUnitIndex][m_texture[textureUnitIndex].size() - 1]);
	}

	void State::bind_vertex_buffer(const ::evo::ogl::VertexBuffer& buf) {
		m_vertexBuffer.push_back(buf.m_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buf.m_buffer);
	}
	void State::unbind_vertex_buffer() {
		m_vertexBuffer.push_back(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void State::rebind_vertex_buffer(const ::evo::ogl::VertexBuffer& buf) {
		m_vertexBuffer[m_vertexBuffer.size() - 1] = buf.m_buffer;
		glBindBuffer(GL_ARRAY_BUFFER, buf.m_buffer);
	}
	void State::revert_vertex_buffer() {
		m_vertexBuffer.pop_back();
		if (m_vertexBuffer.empty()) {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else { 
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[m_vertexBuffer.size() - 1]);
		}
	}

	void State::bind_vertex_array(const ::evo::ogl::VertexArray& buf) {
		m_vertexArray.push_back(buf.m_vao);
		glBindVertexArray(buf.m_vao);
	}
	void State::unbind_vertex_array() {
		m_vertexArray.push_back(0);
		glBindVertexArray(0);
	}
	void State::rebind_vertex_array(const ::evo::ogl::VertexArray& buf) {
		m_vertexArray[m_vertexArray.size() - 1] = buf.m_vao;
		glBindVertexArray(buf.m_vao);
	}
	void State::revert_vertex_array() {
		m_vertexArray.pop_back();
		if (m_vertexArray.empty()) {
			glBindVertexArray(0);
		}
		else {
			glBindVertexArray(m_vertexArray[m_vertexArray.size() - 1]);
		}
	}

	void State::bind_index_buffer(const ::evo::ogl::IndexBuffer& buf) {
		m_indexBuffer.push_back(buf.m_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.m_buffer);
	}
	void State::unbind_index_buffer() {
		m_indexBuffer.push_back(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void State::rebind_index_buffer(const ::evo::ogl::IndexBuffer& buf) {
		m_indexBuffer[m_indexBuffer.size() - 1] = buf.m_buffer;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.m_buffer);
	}
	void State::revert_index_buffer() {
		m_indexBuffer.pop_back();
		if (m_indexBuffer.empty()) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		else { 
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer[m_indexBuffer.size() - 1]);
		}
	}

	void State::bind_technique(const ::evo::ogl::Technique& tch) {
		m_technique.push_back(tch.m_program);
		glUseProgram(tch.m_program);
	}
	void State::unbind_technique() {
		m_technique.push_back(0);
		glUseProgram(0);
	}
	void State::rebind_technique(const ::evo::ogl::Technique& tch) {
		m_technique[m_technique.size() - 1] = tch.m_program;
		glUseProgram(tch.m_program);
	}
	void State::revert_technique() {
		m_technique.pop_back();
		if (m_technique.empty()) {
			glUseProgram(0);
		}
		else {
			glUseProgram(m_technique[m_technique.size() - 1]);
		}
	}

	void State::enable(Capability cap) {
		gl_boolean_t last = m_capabilities[cap.index()].back();
		m_capabilities[cap.index()].push_back(gl_true);
		if(last != gl_true) glEnable(cap.value());
	}
	void State::disable(Capability cap) {
		gl_boolean_t last = m_capabilities[cap.index()].back();
		m_capabilities[cap.index()].push_back(gl_false);
		if (last != gl_false) glDisable(cap.value());
	}
	void State::revert(Capability cap) {
		size_t i = cap.index();
		gl_boolean_t last = m_capabilities[i].back();
		m_capabilities[i].pop_back();
		gl_boolean_t next = m_capabilities[i].back();
		if(next != last) { 
			if (next == gl_true) {
				glEnable(cap.value());
			}
			else {
				glDisable(cap.value());
			}
		}
	}
	bool State::is_enabled(Capability cap) const {
		return m_capabilities[cap.index()].back() == gl_true;
	}

	//todo: replace ptr with something better, consider owning rt (small, stack allocated, trivially? copyable)
	void State::rebind_render_target(RenderTarget* rt) {
		m_renderTarget[m_renderTarget.size() - 1] = rt;
		if (rt == nullptr) {
			RenderTarget::unbind();
		}
		else {
			RenderTarget::Bind(rt);
		}
	}
	void State::bind_render_target(RenderTarget* rt) {
		m_renderTarget.push_back(rt);
		if (rt == nullptr) {
			RenderTarget::unbind();
		}
		else {
			RenderTarget::Bind(rt);
		}
	}
	void State::revert_render_target() {
		m_renderTarget.pop_back();
		RenderTarget* rt = m_renderTarget[m_renderTarget.size() - 1];
		if (rt == nullptr) {
			RenderTarget::unbind();
		}
		else {
			RenderTarget::Bind(rt);
		}
	}
	RenderTarget* State::render_target() const {
		return m_renderTarget[m_renderTarget.size() - 1];
	}
}