#pragma once

#include "types.h"
#include "Graphic.h"
#include "Tree.hpp"

#include "../MyGameEngineSDK/IGameObject.h"
#include "..\MyGameEngineSDK\GameObjectEventHandler.h"

#include <list>
#include <memory>
#include "BBox.hpp"
#include <string>

class GameObject : public Tree<GameObject>, public IGameObject
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

	void* _hModule{nullptr};
	std::unique_ptr<GameObjectEventHandler> _eventHandler;

	bool _isVisible{ true };

public:

	inline const mat4& transform() const override { return _transform; }
	inline vec3& pos() override { return _pos; }
	inline const vec3& pos() const override { return _pos; }

	inline const vec3& left() const override { return _u; }
	inline const vec3& up() const override { return _v; }
	inline const vec3& fwd() const override { return _w; }

	inline bool IsVisible() const override { return _isVisible; }
	inline void Show() override { _isVisible = true; }
	inline void Hide() override { _isVisible = false; }
	
	GameObject();
	GameObject(std::shared_ptr<Graphic> graphic);
	virtual ~GameObject();

	void setEventHandler(const std::string& name);

	void rotate(double degrees, const vec3& axis) override;
	void translate(const vec3& dv) override;

	AABBox aabb() const;

	void paint();
	void step(double dt);

private:
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
};
