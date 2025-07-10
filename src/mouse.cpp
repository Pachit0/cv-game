#include "mouse.h"

HandleMouse::HandleMouse() : m_MousePos({ 0,0 }) {

}

HandleMouse::~HandleMouse() {}

void HandleMouse::update(Camera2D camera) {
	m_MousePos = GetScreenToWorld2D(GetMousePosition(), camera);
}

void HandleMouse::draw() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		//std::cout << "Mouse X: " << mousePos.x << "  " << "Mouse Y: " << mousePos.y << std::endl;
		DrawRectangle(m_MousePos.x, m_MousePos.y, tileSize * scale, tileSize * scale, PURPLE);
	}
}