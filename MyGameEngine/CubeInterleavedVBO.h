#pragma once
#include "Cube.h"
class CubeInterleavedVBO : public Cube
{

	unsigned int _buffer_id;

public:
	CubeInterleavedVBO();
	void draw();

	~CubeInterleavedVBO();

};
