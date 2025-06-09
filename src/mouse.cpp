#include "mouse.h"

handleMouse::handleMouse() : mousePos({ 0,0 }) {

}

handleMouse::~handleMouse() {}

void handleMouse::update(Camera2D camera) {
	mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
}

void handleMouse::draw() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		//std::cout << "Mouse X: " << mousePos.x << "  " << "Mouse Y: " << mousePos.y << std::endl;
		DrawRectangle(mousePos.x, mousePos.y, tileSize * scale, tileSize * scale, PURPLE);
	}
}