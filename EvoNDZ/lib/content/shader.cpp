#include <glad/glad.h>
#include <cstdint>
#include "default_format.h"
#include "shader.h"
#include "../error.h"

evo::data::Shader::Shader(GLenum type) : m_shader(glCreateShader(type)) { }

evo::data::Shader  evo::data::Shader::Load(unsigned char* data, uint64_t length) {
	GLenum shaderType;
	switch (data[0])
	{
	case ShaderSourceType_Fragment:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	case ShaderSourceType_Vertex:
		shaderType = GL_VERTEX_SHADER;
		break;
	case ShaderSourceType_Geometry:
		shaderType = GL_GEOMETRY_SHADER;
		break;
	case ShaderSourceType_Compute:
		shaderType = GL_COMPUTE_SHADER;
		break;
		//default: todo: exception? corrupted data idk
	}
	evo::data::Shader shader(shaderType);
	const char* source = (const char*)(data + 1);
	GLint srcLen = length - 1;
	glShaderSource(shader.shader(), 1, &source, &srcLen);
	glCompileShader(shader.shader());
	GLint compiled = 0;
	glGetShaderiv(shader.shader(), GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader.shader(), GL_INFO_LOG_LENGTH, &infoLogLength);
		char* log = new char[infoLogLength];
		glGetShaderInfoLog(shader.shader(), infoLogLength, &infoLogLength, log);
		glDeleteShader(shader.shader());
		
		EVO_ERROR("%s Shader type: %i", log, shaderType);
	}
	return shader;
}

evo::data::Shader& evo::data::Shader::operator=(evo::data::Shader&& other) noexcept
{
	if (this != &other) {
		glDeleteShader(m_shader);
		m_shader = other.m_shader;
		other.m_shader = 0;
	}
	return *this;
}
