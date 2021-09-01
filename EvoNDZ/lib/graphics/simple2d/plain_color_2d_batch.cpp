#include "../../../include/EvoNDZ/graphics/simple2d/plain_color_2d_batch.h"
#include <glad/glad.h>

namespace evo::s2d
{
	PlainColor2dBatch::PlainColor2dBatch(evo::ogl::DrawMode dm, bool useAngle, bool separateSize, bool useAlpha) : Batch(dm) {
		ogl::Technique::Builder tchb;

		const char* vertex_shader[] {
			R"( #version 460
				    uniform mat3 viewMatrix;
					in vec2 offset;
					in vec2 position; 
					in float depth;
					out vec4 v_color; )",
				( separateSize ? "in vec2 size;" : "in float size;" ),
				( useAngle ? "in float angle;" : "" ),
				( useAlpha ? "in vec4 color;" : "in vec3 color;" ),
				R"(
					void main() {
						vec2 roto = offset * size;
				)",
			    ( useAlpha ? "v_color = color;" : "v_color = vec4(color, 1.0);"),
				( useAngle ?
					R"(		float sina = sin(angle);
							float cosa = cos(angle);
							roto = vec2(roto.x * cosa - roto.y * sina, roto.x * sina + roto.y * cosa);)" : ""
				),
				"gl_Position = vec4((vec3(position + roto, 1.0) * viewMatrix ).xy, depth, 1.0); }"
		};

		char* sherr1 = tchb.attach_shader(ogl::Technique::Builder::VertexShader, vertex_shader, 8);
		if (sherr1) {
			throw std::exception(sherr1);
		}

		const char* fragment_shader[] {
			R"(	#version 460
					in vec4 v_color;
					out vec4 fragColor;
					void main() { fragColor = v_color; } )"
		};

		char* sherr2 = tchb.attach_shader(ogl::Technique::Builder::FragmentShader, fragment_shader, 1);
		if (sherr2) {
			throw std::exception(sherr2);
		}

		auto tch = new ogl::Technique(tchb.link());
		set_technique(tch);

		m_locViewMatrix = tch->uniform_location("viewMatrix");

		std::vector<evo::Batch::AttributeInfo> dynAttribs {
			{ "position", ogl::ShaderType::FVec2() },
			{ "color", useAlpha ? ogl::ShaderType::FVec4() : ogl::ShaderType::FVec3() },
			{ "size", separateSize ? ogl::ShaderType::FVec2() : ogl::ShaderType::Float() },
			{ "depth", ogl::ShaderType::Float() }
		};
		if (useAngle) dynAttribs.push_back({ "angle", ogl::ShaderType::Float() });

		initialize_dynamic_attribs(dynAttribs);
	}

	void PlainColor2dBatch::set_uniforms() {
		glUniformMatrix3fv(m_locViewMatrix, 1, false, m_viewMatrix->data());
	}
}