#include "EventHandler2.h"

extern "C" {
	__declspec(dllexport) GameObjectEventHandler* NewEventHandler2(IGameObject& gameObj_ref) {
		return new EventHandler2(gameObj_ref);
	}
}

EventHandler2::EventHandler2(IGameObject& gameObj_ref) : GameObjectEventHandler(gameObj_ref) {}

void EventHandler2::OnStep(double dt) {
	gameObjRef().rotate(0.1, vec3( 1, 0, 0));
}

void EventHandler2::OnRender() {
	if (rand()%10) gameObjRef().Show();
	else gameObjRef().Hide();
}