#pragma once

#include "Cube.h"
#include "Texture2D.h"

struct CubeImmediateMode : public Cube
{
	Texture2D texture;
	void draw();

	CubeImmediateMode();
};

