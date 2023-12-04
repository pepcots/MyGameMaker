#include "Shader.h"
#include <iostream>
#include <gl/glew.h>

using namespace std;

static GLuint compile(const std::string& src, int target) {
	GLuint id = glCreateShader(target);
	const auto src_ptr = src.c_str();
	glShaderSource(id, 1, &src_ptr, nullptr);
	glCompileShader(id);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		cerr << "Shader compilation error: " <<  infoLog << endl;
		throw exception("");
	}

	return id;
}

void Shader::compile(const std::string& vertex_shader_src, const std::string& fragment_shader_src) {
	
	unload();

	_vertex_sh_id = ::compile( vertex_shader_src, GL_VERTEX_SHADER);
	_fragment_sh_id = ::compile(fragment_shader_src, GL_FRAGMENT_SHADER);
	
	_program_id = glCreateProgram();
	glAttachShader(_program_id, _vertex_sh_id);
	glAttachShader(_program_id, _fragment_sh_id);
	glLinkProgram(_program_id);
}

void Shader::bind() {
	glUseProgram(_program_id);
}

void Shader::unload() {
	if (_program_id) {
		glDeleteProgram(_program_id);
		glDeleteShader(_fragment_sh_id);
		glDeleteShader(_vertex_sh_id);
		_program_id = 0;
		_vertex_sh_id = 0;
		_fragment_sh_id = 0;
	}
}

Shader::~Shader() {
	unload();
}
