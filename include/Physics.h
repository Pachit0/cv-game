#pragma once
#include "Core.h"

class Physics {
private:

	std::vector<Rectangle> obstacles;
public:
	Physics();
	~Physics();
	void objectCoords();
	void draw();
	Vector2 collisionObjectWall(const Vector2& Pos, Vector2 velocity, const float& deltaTime);
};