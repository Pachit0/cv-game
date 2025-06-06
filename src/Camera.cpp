#include "Camera.h"

Camera_c::Camera_c() : cameraVelocity({0,0}) {
	camera.target = { 0 , 0 };
	camera.offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

/*void Camera_c::update(const Player& player) {
	if (player.getPos().x >= 740 && player.getPos().x <= 2300) {
		camera.target.x = player.getPos().x;
	}
	if (player.getPos().y >= 365 && player.getPos().y <= 1070) {
		camera.target.y = player.getPos().y;
	}
}*/

void Camera_c::update(const Player& player) {
		camera.target.x = player.getPos().x;
		camera.target.y = player.getPos().y;
}