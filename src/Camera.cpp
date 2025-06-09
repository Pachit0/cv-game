#include "Camera.h"

Camera_c::Camera_c() : cameraVelocity({0,0}) {
	camera.target = { 0 , 0 };
	camera.offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

void Camera_c::update(const Vector2& pos) {
	if (pos.x >= 740 && pos.y <= 2300) {
		camera.target.x = pos.x;
	}
	if (pos.y >= 365 && pos.y <= 1070) {
		camera.target.y = pos.y;
	}
}