#include "tilemap.h"

Tilemap::Tilemap() {

	m_Image = LoadImage(RESOURCES_PATH "Map/layer1.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_LayerGrass = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/layer2.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_LayerPath = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/layer3-up.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_LayerProps1 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/layer4.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_LayerProps2 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/fences.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_Fences = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/trees1.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_Trees1 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/trees2.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_Trees2 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/insideHouse.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_InsideHouseTexture = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_TilesetRect[i][j] = { tileSize * i * scale, tileSize * j * scale, tileSize * scale, tileSize * scale };
		}
	}

	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 30; j++) {
			groundMap[i][j] = { tileSize * i * scale, tileSize * j * scale, tileSize * scale, tileSize * scale };
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

void Tilemap::update() {
	if (IsKeyPressed(KEY_F)) {
		ToggleFullscreen();
	}
}

void Tilemap::draw() const {
	DrawTexture(m_LayerGrass, 100, 0, WHITE);
	DrawTexture(m_LayerPath, 100, 0, WHITE);
	DrawTexture(m_Fences, 100, -((tileSize - 4) * scale), WHITE);
	DrawTexture(m_LayerProps1, 100, -(tileSize * scale), WHITE);
	DrawTexture(m_LayerProps2, 100, -(tileSize * scale), WHITE);
}

void Tilemap::drawInsideHouse() const {
	DrawTexture(m_InsideHouseTexture, 1425, 175, WHITE);
}

void Tilemap::drawTrees() const {
	DrawTexture(m_Trees1, 100, -(tileSize * scale), WHITE);
	DrawTexture(m_Trees2, 100, -(tileSize * scale), WHITE);
}

void Tilemap::debugLines() const {
	int aspectRatioY = (baseHeight / tileSize) + 2;
	int aspectRatioX = (baseWidth / tileSize) + 6;

	if (IsKeyDown(KEY_C)) {
		for (int y = 0; y < aspectRatioY + 100; y++) {
			for (int x = 0; x < aspectRatioX + 100; x++) {
				float tileX = x * tileSize * scale;
				float tileY = y * tileSize * scale;

				DrawRectangleLines(tileX, tileY, tileSize * scale, tileSize * scale, GREEN);
			}
		}
	}
}
