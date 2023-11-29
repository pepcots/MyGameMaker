#include "EventHandler1.h"

extern "C"{
	__declspec(dllexport) GameObjectEventHandler* NewEventHandler1(IGameObject& gameObj_ref) {
		return new EventHandler1(gameObj_ref);
	}
}

EventHandler1::EventHandler1(IGameObject& gameObj_ref) : GameObjectEventHandler(gameObj_ref) {}

void EventHandler1::OnStep(double dt) {
	gameObjRef().translate(vec3(0.01, 0, 0));
}

void EventHandler1::OnRender() {
	if (rand() & 1) gameObjRef().Show();
	else gameObjRef().Hide();
}
