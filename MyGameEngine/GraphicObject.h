#pragma once

#include "types.h"
#include "Graphic.h"
#include <list>
#include <memory>
#include "BBox.hpp"


template <class T>
class Tree {

private:
	T* _parent_ptr{ nullptr };
	std::list<T> _children;

	void updateChildrenParent() {
		for (Tree& child : _children) {
			child._parent_ptr = static_cast<T*>(this);
			child.updateChildrenParent();
		}
	}

public:
	T* parent() { return _parent_ptr; }
	const T* parent() const { return _parent_ptr; }
	const std::list<T>& children() const { return _children; }
	std::list<T>& children() { return _children; }

	void addChild(T&& child) {
		_children.push_back(std::move(child));
		updateChildrenParent();
	}

	bool removeChild(T&& child) {
		for (auto itr = _children.begin(); itr != _children.end(); ++itr) {
			if (&(*itr) == &child) _children.erase(itr);
			return true;
		}
		return false;
	}

	Tree() = default;
	Tree(Tree&& t) noexcept : _children(std::move(t._children)) {
		if (t._parent_ptr) t._parent_ptr->removeChild((T&&)t);
	}

private:
	Tree(const Tree&) = default;
	Tree& operator=(const Tree&) = default;

};

class GraphicObject : public Tree<GraphicObject>
{
	union {
		mat4 _transform;
		struct {
			vec3 _u; double __uw;
			vec3 _v; double __vw;
			vec3 _w; double __ww;
			vec3 _pos;
		};
	};
	
	std::shared_ptr<Graphic> _graphic;

public:

	inline const mat4& transform() const { return _transform; }
	inline vec3& pos() { return _pos; }
	inline const vec3& pos() const { return _pos; }

	inline const vec3& u() const { return _u; }
	inline const vec3& v() const { return _v; }
	inline const vec3& w() const { return _w; }
	
	GraphicObject();
	GraphicObject(std::shared_ptr<Graphic> graphic);

	void rotate(double degrees, const vec3& axis);
	void translate(const vec3& dv);

	AABBox aabb() const;

	void paint() const;
};
