#pragma once
#include "core.h"

class Tilemap {
private:
	const float m_TileSize;
	const float m_Scale;
	const int m_BaseWidth;
	const int m_BaseHeight;

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

	std::array<std::array<Rectangle, 30>, 60> m_GroundMap;
public:

	Tilemap(const float& TileSize, const float& Scale, const int& BaseWidth, const int& BaseHeight);
	~Tilemap();

	void draw() const;
	void drawInsideHouse() const;
	void drawTrees() const;
	void debugLines() const;
	const std::array<std::array<Rectangle, 30>, 60>& getTileMap() const;
};
