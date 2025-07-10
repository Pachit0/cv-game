#pragma once
#include "Core.h"
#include "Player.h"

class MainCamera {
private:
	Camera2D m_Camera;
	Vector2 m_CameraVelocity;
public:
	MainCamera();
	~MainCamera();
	void update(const Vector2& pos);
	Camera2D getCamera() const;
};