#include "Camera.h"

MainCamera::MainCamera() : m_CameraVelocity({0,0}) {
	m_Camera.target = { 0 , 0 };
	m_Camera.offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_Camera.rotation = 0.0f;
	m_Camera.zoom = 1.0f;
}

MainCamera::~MainCamera() {}

void MainCamera::update(const Vector2& pos) {
	switch (currentLevel) {
	case village: {
		if (pos.x >= 740 && pos.x <= 2300) {
			m_Camera.target.x = pos.x;
		}
		if (pos.y >= 365 && pos.y <= 1070) {
			m_Camera.target.y = pos.y;
		}
		break;
		}
	case insideHouse: {
		m_Camera.target.x = 1700;
		m_Camera.target.y = 475;
		break;
		}
	default:
		break;
	}
}

Camera2D MainCamera::getCamera() const {
	return m_Camera;
}