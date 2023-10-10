#pragma once
#include "Cube.h"
class CubeWireframeIVBO : public Cube
{
	unsigned int _buffer_id;
	unsigned int _index_bufer_id;

public:
	CubeWireframeIVBO();
	void draw();
	~CubeWireframeIVBO();

};

