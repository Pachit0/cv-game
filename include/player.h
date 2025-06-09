#pragma once
#include "Core.h"

enum direction {
	DOWN,
	LEFT_DOWN,
	LEFT_UP,
	UP,
	RIGHT_UP,
	RIGHT_DOWN
};

class Player {
private:
	unsigned frameNum; // character frames
	unsigned frameDelay; // animation speed
	unsigned frameDelayCount;
	unsigned frameIndex;

	Vector2 Pos;

	Rectangle movement_Rect[6][8];
	Vector2 velocity;

	float speed;
	int directions;

public:
	Texture2D idle;
	Texture2D walk;
	Image image;

	Player();
	~Player();

	void inputHandling();
	void handleCurrentDirection();
	void Update(const float& deltaTime);
	void Draw();

	Vector2 getPos() const { return Pos; }
	void setPos(const Vector2& newPos) { Pos = newPos; }
	Vector2 getVelocity() const { return velocity; }
	void setVelocity(const Vector2& newVelocity) { velocity = newVelocity; }
};