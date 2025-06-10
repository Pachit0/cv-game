#include "tilemap.h"

Tilemap::Tilemap() {

	image = LoadImage(RESOURCES_PATH "The Fan-tasy Tileset/Art/Ground Tileset/Tileset_Ground.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	tileset = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/layer1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	layerGrass = LoadTextureFromImage(image);
	UnloadImage(image);
	
	image = LoadImage(RESOURCES_PATH "Map/layer2.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	layerPath = LoadTextureFromImage(image);
	UnloadImage(image);
	
	image = LoadImage(RESOURCES_PATH "Map/layer3-up.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	layerProps1 = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/layer4.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	layerProps2 = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/fences.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	fences = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/trees1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	trees1 = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/trees2.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	trees2 = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/insideHouse.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	insideHouseTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			tileset_rect[i][j] = { tileSize * i * scale, tileSize * j * scale, tileSize * scale, tileSize * scale };
		}
	}

	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 30; j++) {
			groundMap[i][j] = { tileSize * i * scale, tileSize * j * scale, tileSize * scale, tileSize * scale };
		}
	}
}

Tilemap::~Tilemap() {
	UnloadTexture(tileset);
	UnloadTexture(layerGrass);
	UnloadTexture(layerPath);
	UnloadTexture(layerProps1);
	UnloadTexture(layerProps2);
	UnloadTexture(fences);
	UnloadTexture(trees1);
	UnloadTexture(trees2);
	UnloadTexture(insideHouseTexture);
}

void Tilemap::update() {
	if (IsKeyPressed(KEY_F)) {
		ToggleFullscreen();
	}
}

void Tilemap::draw() const {
	DrawTexture(layerGrass, 100, 0, WHITE);
	DrawTexture(layerPath, 100, 0, WHITE);
	DrawTexture(fences, 100, -((tileSize - 4) * scale), WHITE);
	DrawTexture(layerProps1, 100, -(tileSize * scale), WHITE);
	DrawTexture(layerProps2, 100, -(tileSize * scale), WHITE);

}
void Tilemap::drawInsideHouse() const {
	DrawTexture(insideHouseTexture, 1425, 175, WHITE);
}

void Tilemap::drawTrees() const {
	DrawTexture(trees1, 100, -(tileSize * scale), WHITE);
	DrawTexture(trees2, 100, -(tileSize * scale), WHITE);
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