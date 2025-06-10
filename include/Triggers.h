#pragma once
#include "Core.h"

class Triggers {
private:
	bool read;
	bool note;
	bool noteOpened;
	bool enterHouse;

	bool tv;
	bool tvOpened;
	bool tvWatching;

	bool exitHouse;

	std::vector<std::vector<Rectangle>> triggersLevel;

	Texture2D scroll;
	Texture2D paper;

	Image image;
public:
	Triggers();
	~Triggers();
	void triggerCoords();
	void collisionTrigger(const Vector2& Pos);
	void update(const Vector2& Pos);
	void draw(const Vector2& Pos);
};