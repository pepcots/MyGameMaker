#include "GraphicObject.h"
#include <GL/glew.h>

GraphicObject::GraphicObject() : _transform(glm::identity<mat4>()), _parent(nullptr) {}
GraphicObject::GraphicObject(std::shared_ptr<Graphic> graphic) : _transform(glm::identity<mat4>()), _parent(nullptr), _graphic(graphic) {}

void GraphicObject::paint() {
	glPushMatrix();
	glMultMatrixd(&_transform[0].x);
	if(_graphic.get()) _graphic->draw();
	for (auto child : _children) child->paint();
	glPopMatrix();
}

void GraphicObject::addChild(GraphicObject* child) {
	if (child->_parent == this) return;
	if (child->_parent) child->_parent->removeChild(child);
	_children.insert(child);
	child->_parent = this;
}

void GraphicObject::removeChild(GraphicObject* child) {
	if (_children.erase(child)) child->_parent = nullptr;
}

GraphicObject::~GraphicObject() {
	if (_parent) _parent->removeChild(this);
	for (auto child : _children) child->_parent = nullptr;
}
