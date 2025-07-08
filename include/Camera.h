#pragma once
#include "Core.h"
#include "Player.h"

class Camera_c {
private:
	Camera2D camera;
	Vector2 cameraVelocity;
public:
	Camera_c();
	~Camera_c();
	void update(const Vector2& pos);
	Camera2D getCamera() const;
};