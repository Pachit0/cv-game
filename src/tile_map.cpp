#include "tile_map.h"

Tilemap::Tilemap(const float& TileSize, const float& Scale, const int& BaseWidth, const int& BaseHeight)
		: m_TileSize(TileSize), m_Scale(Scale), m_BaseHeight(BaseHeight), m_BaseWidth(BaseWidth)	{

	m_Image = LoadImage(RESOURCES_PATH "Map/layer1.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_LayerGrass = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/layer2.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_LayerPath = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/layer3-up.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_LayerProps1 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/layer4.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_LayerProps2 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/fences.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_Fences = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/trees1.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_Trees1 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/trees2.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_Trees2 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/insideHouse.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_InsideHouseTexture = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_TilesetRect[i][j] = { m_TileSize * i * m_Scale, m_TileSize * j * m_Scale, m_TileSize * m_Scale, m_TileSize * m_Scale };
		}
	}

	for (int x = 0; x < m_GroundMap.size(); x++) {
		for (int y = 0; y < m_GroundMap[x].size(); y++) {
			m_GroundMap[x][y] = { m_TileSize * x * m_Scale, m_TileSize * y * m_Scale, m_TileSize * m_Scale, m_TileSize * m_Scale };
		}
	}
}

Tilemap::~Tilemap() {
	UnloadTexture(m_LayerGrass);
	UnloadTexture(m_LayerPath);
	UnloadTexture(m_LayerProps1);
	UnloadTexture(m_LayerProps2);
	UnloadTexture(m_Fences);
	UnloadTexture(m_Trees1);
	UnloadTexture(m_Trees2);
	UnloadTexture(m_InsideHouseTexture);
}

void Tilemap::draw() const {
	DrawTexture(m_LayerGrass, 100, 0, WHITE);
	DrawTexture(m_LayerPath, 100, 0, WHITE);
	DrawTexture(m_Fences, 100, -((m_TileSize - 4) * m_Scale), WHITE);
	DrawTexture(m_LayerProps1, 100, -(m_TileSize * m_Scale), WHITE);
	DrawTexture(m_LayerProps2, 100, -(m_TileSize * m_Scale), WHITE);
}

void Tilemap::drawInsideHouse() const {
	DrawTexture(m_InsideHouseTexture, 1425, 175, WHITE);
}

void Tilemap::drawTrees() const {
	DrawTexture(m_Trees1, 100, -(m_TileSize * m_Scale), WHITE);
	DrawTexture(m_Trees2, 100, -(m_TileSize * m_Scale), WHITE);
}

void Tilemap::debugLines() const {
	int aspectRatioY = (m_BaseHeight / m_TileSize) + 2;
	int aspectRatioX = (m_BaseWidth / m_TileSize) + 6;

	if (IsKeyDown(KEY_C)) {
		for (int y = 0; y < aspectRatioY + 100; y++) {
			for (int x = 0; x < aspectRatioX + 100; x++) {
				float tileX = x * m_TileSize * m_Scale;
				float tileY = y * m_TileSize * m_Scale;

				DrawRectangleLines(tileX, tileY, m_TileSize * m_Scale, m_TileSize * m_Scale, GREEN);
			}
		}
	}
}

const std::array<std::array<Rectangle, 30>, 60>& Tilemap::getTileMap() const	{
	return m_GroundMap;
}