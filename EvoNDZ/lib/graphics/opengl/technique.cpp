#include <glad\glad.h>
#include "../../../include/EvoNDZ/graphics/opengl/technique.h"

namespace evo::ogl
{
	const evo::ogl::gl_uint_t Technique::Builder::VertexShader = GL_VERTEX_SHADER;
	const evo::ogl::gl_uint_t Technique::Builder::FragmentShader = GL_FRAGMENT_SHADER;
	const evo::ogl::gl_uint_t Technique::Builder::GeometryShader = GL_GEOMETRY_SHADER;
	const evo::ogl::gl_uint_t Technique::Builder::ComputeShader = GL_COMPUTE_SHADER;

	Technique::Builder::Builder() : m_compiled(GL_TRUE), m_program(glCreateProgram()) { }

	char* Technique::Builder::attach_shader(gl_enum_t type, const char* const* srcv, size_t srcn) {
		gl_uint_t shader = glCreateShader(type);
		glShaderSource(shader, srcn, srcv, 0);
		glCompileShader(shader);
		gl_int_t compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE) {
			gl_int_t infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* log = new char[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, log);
			m_compiled = GL_FALSE;
			glDeleteShader(shader);
			shader = gl_invalid;
			return log;
		}
		m_shaders.push_back(AttachedShader(shader, true));
		glAttachShader(m_program, shader);
		return nullptr;
	}

	char* Technique::Builder::attach_shader(gl_enum_t t, const char* src) {
		return attach_shader(t, &src, 1);
	}

	/*void Technique::Builder::attachShader(const dgl::data::Shader& shader) {
		m_shaders.push_back(AttachedShader(shader.shader(), false));
		glAttachShader(m_program, shader.shader());
	}
	void Technique::Builder::attachShader(dgl::data::Shader&& shader) {
		m_shaders.push_back(AttachedShader(shader.shader(), true));
		glAttachShader(m_program, shader.shader());
	}*/
	Technique Technique::Builder::link() {
		if (m_compiled == GL_FALSE) return Technique(gl_invalid);
		glLinkProgram(m_program);
		for (size_t i = 0; i < m_shaders.size(); ++i) {
			glDetachShader(m_program, m_shaders[i].shader);
			if(m_shaders[i].owned) glDeleteShader(m_shaders[i].shader); 
		}
		return Technique(m_program);
	}

	Technique::Technique(gl_uint_t program) : m_program(program) { }

	Technique::~Technique() { 
		glDeleteProgram(m_program); 
	}

	Technique& Technique::operator=(Technique&& other) noexcept
	{
		if (this != &other) {
			glDeleteProgram(m_program);
			m_program = other.m_program;
			other.m_program = 0;
		}
		return *this;
	}

	gl_int_t Technique::uniform_location(const gl_char_t* name) const {
		return glGetUniformLocation(m_program, name);
	}

	gl_int_t Technique::attrib_location(const gl_char_t* name) const {
		return glGetAttribLocation(m_program, name);
	}

	/*Technique Technique::Load(unsigned char* data, uint64_t length) {
		Technique::Builder builder;
		size_t di = 0;
		while (di < length) {
			size_t size = data[di++] + 1;
			std::string name = std::string(size, ' ');
			std::copy(data + di, data + di + size, name.data());
			di += size;
			builder.attachShader(dgl::data::ContentStorage<dgl::data::Shader>::GetByName(name));
		}
		return builder.link();
	}*/
}