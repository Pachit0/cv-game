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
	unsigned m_FrameNum; // character frames
	unsigned m_FrameDelay; // animation speed
	unsigned m_FrameDelayCount;
	unsigned m_FrameIndex;

	Vector2 m_Pos;
	Vector2 m_Velocity;

	Rectangle m_Movement_Rect[6][8];

	float m_Speed;
	int m_Directions;

	Texture2D m_Idle;
	Texture2D m_Walk;
	Image m_Image;
public:

	Player();
	~Player();

	void inputHandling();
	void handleCurrentDirection();
	void Update(const float& deltaTime);
	void Draw();

	Vector2 getPos() const;
	void setPos(const Vector2& newPos);
	Vector2 getVelocity() const;
	void setVelocity(const Vector2& newVelocity);
};