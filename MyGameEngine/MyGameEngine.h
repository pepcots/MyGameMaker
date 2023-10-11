#pragma once

#include <chrono>

#include "types.h"
#include "Camera.h"

class MyGameEngine
{
public:
	Camera camera;

	MyGameEngine();
	void step(std::chrono::duration<double> dt);
	void render();
};

