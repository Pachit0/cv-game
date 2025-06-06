#pragma once
#include "Core.h"
#include "Player.h"

class Camera_c {
private:
	Camera2D camera;
	Vector2 cameraVelocity; // 0 0
public:
	Camera_c();
	void update(const Player& player);
	Camera2D getCamera() const { return camera; }
};