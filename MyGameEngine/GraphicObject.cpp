#include "GraphicObject.h"
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

GraphicObject::GraphicObject() : _transform(glm::identity<mat4>()) {}
GraphicObject::GraphicObject(std::shared_ptr<Graphic> graphic) : _transform(glm::identity<mat4>()), _graphic(graphic) {}

void GraphicObject::rotate(double degrees, const vec3& axis) {
	_transform = glm::rotate(_transform, glm::radians(degrees), axis);
}

void GraphicObject::translate(const vec3& dv) {
	_transform = glm::translate(_transform, dv);
}

void GraphicObject::paint() const {

	glPushMatrix();
	glMultMatrixd(&_transform[0].x);
	if (_graphic.get()) _graphic->draw();
	for (auto& child : children()) child.paint();
	glPopMatrix();
}
