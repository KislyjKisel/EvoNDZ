#include "../../include/EvoNDZ/graphics/batch.h"
#include <glad/glad.h>
#include "../../include/EvoNDZ/graphics/opengl/enum/buffer_usage.h"
#include "../../include/EvoNDZ/graphics/opengl/enum/shader_type.h"
#include "../../include/EvoNDZ/graphics/opengl/state.h"
#include "../../include/EvoNDZ/app/application.h"


namespace evo
{
	void Batch::render(const void* data, size_t dataSize, unsigned instances) {
		if (instances == 0) return;
		app::gl()->bind_vertex_array(m_vertexArray);
		app::gl()->bind_technique(*m_technique);

		if (m_vbDynamicSize < dataSize) {
			m_vbDynamic.data(data, dataSize, ogl::BufferUsage::DynamicDraw());
			setup_dynamic_attribs();
		}
		else {
			m_vbDynamic.sub_data(data, dataSize, 0);
		}
		set_uniforms();
		glDrawElementsInstanced(m_drawMode.value(), m_indexCount, m_indexType, nullptr, (ogl::gl_sizei_t)instances);

		app::gl()->revert_technique();
		app::gl()->revert_vertex_array();
	}

	template<ogl::Index T>
	void Batch::set_static_mesh(const void* data, ogl::gl_sizeiptr_t dataSize, const T* indices, size_t indexCount) {
		m_vbStatic.data(data, dataSize, ogl::BufferUsage::StaticDraw());
		m_indexBuffer.data(indices, indexCount, ogl::BufferUsage::StaticDraw());
		m_indexType = ogl::index_type_id<T>();
		m_indexCount = indexCount;
	}

	template void Batch::set_static_mesh<uint8_t>(const void*, ogl::gl_sizeiptr_t, const uint8_t*, size_t);
	template void Batch::set_static_mesh<uint16_t>(const void*, ogl::gl_sizeiptr_t, const uint16_t*, size_t);
	template void Batch::set_static_mesh<uint32_t>(const void*, ogl::gl_sizeiptr_t, const uint32_t*, size_t);

	void Batch::set_technique(ogl::Technique* ptr) {
		m_technique = std::unique_ptr<ogl::Technique>(ptr);
	}

	void Batch::init_static_attribs() {
		GLsizei stride = 0;
		for (auto& a : m_attrStatic) {
			a.offset = stride;
			a.location = m_technique->attrib_location(a.glslName);
			stride += a.glslType.size();
		}
		m_strideStatic = stride;
	}

	void Batch::init_dynamic_attribs() {
		GLsizei stride = 0;
		for (auto& a : m_attrDynamic) {
			a.offset = stride;
			a.location = m_technique->attrib_location(a.glslName);
			stride += a.glslType.size();
		}
		m_strideDynamic = stride;
	}

	void Batch::setup_static_attribs() {
		app::gl()->bind_vertex_array(m_vertexArray);
		app::gl()->bind_vertex_buffer(m_vbStatic);
		app::gl()->bind_index_buffer(m_indexBuffer);
		for (const auto& a : m_attrStatic) {
			glEnableVertexAttribArray(a.location);
			glVertexAttribPointer(a.location, a.glslType.count(), a.glslType.type(), GL_FALSE, m_strideStatic, (void*)a.offset);
		}
		app::gl()->revert_vertex_array();
		app::gl()->revert_index_buffer();
		app::gl()->revert_vertex_buffer();
	}

	void Batch::setup_dynamic_attribs() {
		app::gl()->bind_vertex_array(m_vertexArray);
		app::gl()->bind_vertex_buffer(m_vbDynamic);
		for (const auto& a : m_attrDynamic) {
			glEnableVertexAttribArray(a.location);
			glVertexAttribPointer(a.location, a.glslType.count(), a.glslType.type(), GL_FALSE, m_strideDynamic, (void*)a.offset);
			glVertexAttribDivisor(a.location, 1);
		}
		app::gl()->revert_vertex_array();
		app::gl()->revert_vertex_buffer();
	}

	void Batch::disable_static_attribs() {
		app::gl()->bind_vertex_array(m_vertexArray);
		for (const auto& a : m_attrDynamic) {
			glDisableVertexAttribArray(a.location);
		}
		app::gl()->revert_vertex_array();
	}

	void Batch::disable_dynamic_attribs() {
		app::gl()->bind_vertex_array(m_vertexArray);
		for (const auto& a : m_attrDynamic) {
			glDisableVertexAttribArray(a.location);
		}
		app::gl()->revert_vertex_array();
	}

	void Batch::initialize_static_attribs(const std::vector<Batch::AttributeInfo>& attrStatic) {
		m_attrStatic = attrStatic;
		init_static_attribs();
		setup_static_attribs();
	}

	void Batch::initialize_dynamic_attribs(const std::vector<Batch::AttributeInfo>& attrDynamic) {
		m_attrDynamic = attrDynamic;
		init_dynamic_attribs();
		setup_dynamic_attribs();
	}

	void Batch::replace_static_attribs(const std::vector<AttributeInfo>& attribs) {
		disable_static_attribs();
		initialize_static_attribs(attribs);
	}

	void Batch::replace_dynamic_attribs(const std::vector<AttributeInfo>& attribs) {
		disable_dynamic_attribs();
		initialize_dynamic_attribs(attribs);
	}
}