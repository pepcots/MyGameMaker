#pragma once
#include "Cube.h"

class CubeVertexBuffer : public Cube
{

	unsigned int _vertex_buffer_id;
	unsigned int _color_buffer_id;

public:
	CubeVertexBuffer();
	void draw();

};

