#pragma once

#include "IGameObject.h"


class GameObjectEventHandler {

private:
	IGameObject& _gameObj_ref;

protected:
	inline IGameObject& gameObjRef() { return _gameObj_ref; }
	inline const IGameObject& gameObjRef() const { return _gameObj_ref; }
	
public:
	explicit GameObjectEventHandler(IGameObject& gameObj_ref);
	virtual ~GameObjectEventHandler() = default;

	virtual void OnRender() = 0;
	virtual void OnStep(double dt) = 0;

private:
	GameObjectEventHandler(const GameObjectEventHandler&) = delete;
	GameObjectEventHandler& operator=(const GameObjectEventHandler&) = delete;
	
};

typedef GameObjectEventHandler* (*NewEventHandler_t)(IGameObject&);
