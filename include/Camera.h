#pragma once
#include "Core.h"
#include "gameEnums.h"

class MainCamera {
private:
	Camera2D m_Camera;
	Vector2 m_CameraVelocity;
public:
	MainCamera();
	~MainCamera();
	void update(const Vector2& pos, Scene::Level currentLevel);
	Camera2D getCamera() const;
};