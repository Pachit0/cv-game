#include "tile_map.h"

Tilemap::Tilemap(const float& TileSize, const float& Scale, const int& BaseWidth, const int& BaseHeight)
		: m_TileSize(TileSize), m_Scale(Scale), m_BaseHeight(BaseHeight), m_BaseWidth(BaseWidth)	{
	
	m_LayerGrass = LoadFilteredTexture(RESOURCES_PATH "Map/layer1.png");
	m_LayerPath = LoadFilteredTexture(RESOURCES_PATH "Map/layer2.png");
	m_LayerProps1 = LoadFilteredTexture(RESOURCES_PATH "Map/layer3-up.png");
	m_LayerProps2 = LoadFilteredTexture(RESOURCES_PATH "Map/layer4.png");
	m_Fences = LoadFilteredTexture(RESOURCES_PATH "Map/fences.png");
	m_Trees1 = LoadFilteredTexture(RESOURCES_PATH "Map/trees1.png");
	m_Trees2 = LoadFilteredTexture(RESOURCES_PATH "Map/trees2.png");
	m_InsideHouseTexture = LoadFilteredTexture(RESOURCES_PATH "Map/insideHouse.png");


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
	DrawTextureEx(m_LayerGrass, { m_GroundMap[2][0].x, m_GroundMap[0][0].y }, 0.0f, m_Scale, WHITE);
	DrawTextureEx(m_LayerPath, { m_GroundMap[2][0].x, m_GroundMap[0][0].y }, 0.0f, m_Scale, WHITE);
	DrawTextureEx(m_LayerProps1, { m_GroundMap[2][0].x, m_GroundMap[0][0].y }, 0.0f, m_Scale, WHITE);
	DrawTextureEx(m_LayerProps2, { m_GroundMap[2][0].x, m_GroundMap[0][0].y },0.0f,m_Scale, WHITE);
}

void Tilemap::drawInsideHouse() const {
	DrawTextureEx(m_InsideHouseTexture, { m_GroundMap[30][0].x - 15, m_GroundMap[0][4].y - 17 }, 0.0f, m_Scale, WHITE);
}

void Tilemap::drawTrees() const {
	DrawTextureEx(m_Fences, { m_GroundMap[2][0].x, m_GroundMap[0][0].y }, 0.0f, m_Scale, WHITE);
	DrawTextureEx(m_Trees1, { m_GroundMap[2][0].x, m_GroundMap[0][0].y}, 0.0f, m_Scale, WHITE);
	DrawTextureEx(m_Trees2, { m_GroundMap[2][0].x, m_GroundMap[0][0].y }, 0.0f, m_Scale, WHITE);
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