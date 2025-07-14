#include "mouse.h"

HandleMouse::HandleMouse(const float& TileSize, const float& Scale)
	: m_MousePos({ 0,0 }), m_TileSize(TileSize), m_Scale(Scale) {

}

HandleMouse::~HandleMouse() {}

void HandleMouse::update(Camera2D camera) {
	m_MousePos = GetScreenToWorld2D(GetMousePosition(), camera);
}

void HandleMouse::draw() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		//std::cout << "Mouse X: " << mousePos.x << "  " << "Mouse Y: " << mousePos.y << std::endl;
		DrawRectangle(m_MousePos.x, m_MousePos.y, m_TileSize * m_Scale, m_TileSize * m_Scale, PURPLE);
	}
}