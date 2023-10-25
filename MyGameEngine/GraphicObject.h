#pragma once

#include "types.h"
#include "Graphic.h"
#include <glm/ext/matrix_transform.hpp>
#include <list>
#include <memory>


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
	mat4 _transform;
	std::shared_ptr<Graphic> _graphic;

public:

	inline vec3& pos() { return (vec3&)(_transform[3]); }
	
	GraphicObject();
	GraphicObject(std::shared_ptr<Graphic> graphic);
	
	inline void rotate(double rads, const vec3& axis) { _transform = glm::rotate(_transform, rads, axis); }

	void paint() const;
};
