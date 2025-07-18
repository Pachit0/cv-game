#pragma once

#include "core.h"

class Entity {
private:

	Vector2 m_Position;
	Vector2 m_Velocity;

	float m_Speed;

	const float m_TileSize;
public:

	Entity(const float& TileSize);
	virtual ~Entity();

	virtual void update(const float& deltaTime) = 0; // it must be overidden by any derived class that's why the function is "= 0"
	virtual void draw() = 0;


	Vector2 getEntityPosition() const;
	void setEntityPosition(const Vector2& newPosition);

	Vector2 getEntityVelocity() const;
	Vector2& getEntityVelocity();
	void setEntityVelocity(const Vector2& newVelocity);

	void setEntitySpeed(const float& newSpeed);
	float getEntitySpeed();
};