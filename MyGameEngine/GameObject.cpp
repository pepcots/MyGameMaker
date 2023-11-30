#include "GameObject.h"
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>
#define NOMINMAX
#include <Windows.h>
#include <string>

using namespace std;

GameObject::GameObject() : _transform(glm::identity<mat4>()) {}
GameObject::GameObject(std::shared_ptr<Graphic> graphic) : _transform(glm::identity<mat4>()), _graphic(graphic) {}

void GameObject::rotate(double degrees, const vec3& axis) {
	_transform = glm::rotate(_transform, glm::radians(degrees), axis);
}

void GameObject::translate(const vec3& dv) {
	_transform = glm::translate(_transform, dv);
}

static inline void glVec3(const vec3& v) { glVertex3dv(&v.x); }

static void drawAABBox(const AABBox& aabb) {
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	glVec3(aabb.a());
	glVec3(aabb.b());
	glVec3(aabb.c());
	glVec3(aabb.d());
	glVec3(aabb.a());

	glVec3(aabb.e());
	glVec3(aabb.f());
	glVec3(aabb.g());
	glVec3(aabb.h());
	glVec3(aabb.e());
	glEnd();

	glBegin(GL_LINES);
	glVec3(aabb.h());
	glVec3(aabb.d());
	glVec3(aabb.f());
	glVec3(aabb.b());
	glVec3(aabb.g());
	glVec3(aabb.c());
	glEnd();
}

AABBox GameObject::aabb() const {
	AABBox aabbox;
	if (_graphic.get()) aabbox = _graphic->aabb;
	else if (children().empty()) {
		aabbox.min = vec3(0);
		aabbox.max = vec3(0);
	}

	for (const auto& child : children()) {
		const auto child_aabb = (child.transform() * child.aabb()).AABB();
		aabbox.min = glm::min(aabbox.min, child_aabb.min);
		aabbox.max = glm::max(aabbox.max, child_aabb.max);
	}

	return aabbox;
}

void GameObject::step(double dt) {
	if (_eventHandler.get()) _eventHandler->OnStep(dt);
	for (auto& child : children()) child.step(dt);
}

void GameObject::paint() {

	if (_eventHandler.get()) _eventHandler->OnRender();

	if (!IsVisible()) return;

	glPushMatrix();
	glMultMatrixd(&_transform[0].x);

	glColor3ub(128, 0, 0);
	drawAABBox(aabb());

	if (_graphic.get()) _graphic->draw();
	for (auto& child : children()) child.paint();
	
	glPopMatrix();
}

void GameObject::setEventHandler(const std::string& name) {

	if (_hModule) {
		_eventHandler.reset();
		FreeLibrary(static_cast<HMODULE>(_hModule));
	}

	if (!name.empty()) {
#ifdef _DEBUG
		const string dllFolder("../x64/Debug/");
#else
		const string dllFolder("../x64/Release/");
#endif
		_hModule = LoadLibrary((dllFolder + name + ".dll").c_str());
		auto NewEventHandler = (NewEventHandler_t)GetProcAddress(static_cast<HMODULE>(_hModule), (string("New") + name).c_str());
		_eventHandler.reset(NewEventHandler(*this));
	}
}

GameObject::~GameObject() {
	setEventHandler("");
}
