#pragma once
#include "Core.h"

class handleMouse {
private:
	Vector2 mousePos;
public:

	handleMouse();
	~handleMouse();

	void update(Camera2D camera);
	void draw();

};