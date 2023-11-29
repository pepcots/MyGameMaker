#pragma once

#include "../MyGameEngineSDK/GameObjectEventHandler.h"

class EventHandler2 : public GameObjectEventHandler
{
public:
	explicit EventHandler2(IGameObject& gameObj_ref);
	void OnRender() override;
	void OnStep(double dt) override;
};

