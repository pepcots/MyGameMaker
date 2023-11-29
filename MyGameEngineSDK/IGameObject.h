#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

using vec3 = glm::dvec3;
using mat4 = glm::dmat4;

class IGameObject
{

public:
	virtual const mat4& transform() const = 0;
	virtual const vec3& left() const = 0;
	virtual const vec3& up() const = 0;
	virtual const vec3& fwd() const = 0;
	virtual const vec3& pos() const = 0;
	virtual vec3& pos() = 0;

	virtual bool IsVisible() const = 0;
	virtual void Show() = 0;
	virtual void Hide() = 0;

	virtual void translate(const vec3& dx) = 0;
	virtual void rotate(double degs, const vec3& axis) = 0;
};

