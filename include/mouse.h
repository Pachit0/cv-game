#pragma once
#include "Core.h"

class HandleMouse {
private:
	const float m_TileSize;
	const float m_Scale;
	Vector2 m_MousePos;
public:

	HandleMouse(const float& TileSize, const float& Scale);
	~HandleMouse();

	void update(Camera2D camera);
	void draw();

};