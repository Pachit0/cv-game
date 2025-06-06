#pragma once
#include "Core.h"

class Tilemap {
private:
	Vector2 mousePos;
	Rectangle tileset_rect[12][12];

	Texture2D tileset;
	Texture2D layerGrass;
	Texture2D layerPath;
	Texture2D layerProps1;
	Texture2D layerProps2;
	Texture2D fences;
	Texture2D house;
	Texture2D trees1;
	Texture2D trees2;


	Image image;
public:

	Tilemap();
	~Tilemap();

	void update(Camera2D camera);
	void draw(Vector2 pos);
	void drawTrees() const;
	void debugLines();
};