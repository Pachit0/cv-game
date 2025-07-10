#pragma once
#include "Core.h"

class HandleMouse {
private:
	Vector2 m_MousePos;
public:

	HandleMouse();
	~HandleMouse();

	void update(Camera2D camera);
	void draw();

};