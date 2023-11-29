#pragma once

#include "../MyGameEngineSDK/GameObjectEventHandler.h"

class EventHandler1 : public GameObjectEventHandler
{
public:
	explicit EventHandler1(IGameObject& gameObj_ref);
	void OnRender() override;
	void OnStep(double dt) override;
};

