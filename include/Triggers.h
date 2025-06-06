#pragma once
#include "Core.h"

class Triggers {
private:
	bool read;
	bool note;
	bool noteOpened;
	std::vector<Rectangle> triggers;

	Texture2D scroll;
public:
	Triggers();
	~Triggers();
	void triggerCoords();
	void collisionTrigger(Vector2 Pos);
	void update(Vector2 Pos);
	void draw(Vector2 Pos);
};