#pragma once
#include "Core.h"

class Tilemap {
private:
	Rectangle m_TilesetRect[12][12];

	Texture2D m_LayerGrass;
	Texture2D m_LayerPath;
	Texture2D m_LayerProps1;
	Texture2D m_LayerProps2;
	Texture2D m_Fences;
	Texture2D m_Trees1;
	Texture2D m_Trees2;
	Texture2D m_InsideHouseTexture;

	Image m_Image;

public:

	Tilemap();
	~Tilemap();

	void update();
	void draw() const;
	void drawInsideHouse() const;
	void drawTrees() const;
	void debugLines() const;
};
