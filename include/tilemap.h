#pragma once
#include "Core.h"

class Tilemap {
private:
	Rectangle tileset_rect[12][12];

	Texture2D tileset;
	Texture2D layerGrass;
	Texture2D layerPath;
	Texture2D layerProps1;
	Texture2D layerProps2;
	Texture2D fences;
	Texture2D trees1;
	Texture2D trees2;
	Texture2D insideHouseTexture;

	Image image;
public:

	Tilemap();
	~Tilemap();

	void update();
	void draw() const;
	void drawInsideHouse() const;
	void drawTrees() const;
	void debugLines() const;
};