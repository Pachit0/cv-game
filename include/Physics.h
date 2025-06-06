#pragma once
#include "Core.h"

class Physics {
private:

	std::vector<Rectangle> obstacles;
public:
	Physics();
	~Physics();
	void objectCoords();
	void draw(Vector2 Pos);
	Vector2 collisionObjectWall(Vector2 Pos, Vector2 velocity, float deltaTime);
};