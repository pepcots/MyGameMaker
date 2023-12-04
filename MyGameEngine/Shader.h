#pragma once

#include <string>

class Shader
{
	unsigned int _vertex_sh_id{0};
	unsigned int _fragment_sh_id{0};
	unsigned int _program_id{0};

public:
	Shader() = default;
	~Shader();
	

	void compile(const std::string& vertex_shader_src, const std::string& fragment_shader_src);
	void unload();
	void bind();
	
private:
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

};

