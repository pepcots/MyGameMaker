#pragma once

#include <vector>
#include <memory>
#include <string>

#include "types.h"
#include "Graphic.h"
#include "Texture2D.h"

class Mesh : public Graphic
{
public:
	enum Formats { F_V3, F_V3C4, F_V3T2 };
	struct V3 { vec3f v; };
	struct V3C4 { vec3f v; vec4f c; };
	struct V3T2 { vec3f v; vec2f t; };

private:
	const enum Formats _format;

	unsigned int _vertex_buffer_id{0};
	const unsigned int _numVerts{0};

	unsigned int _indexs_buffer_id{0};
	const unsigned int _numIndexs{0};
	
public:
	
	static std::vector<std::shared_ptr<Mesh>> loadFromFile(const std::string& path);
	
	Texture2D::Ptr texture;

	Mesh(Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* indexs_data=nullptr, unsigned int numIndexs=0);
	Mesh(Mesh&& b) noexcept;
	void draw();
	~Mesh();

private:
	Mesh(const Mesh& cpy) = delete;
	Mesh& operator=(const Mesh&) = delete;
};

