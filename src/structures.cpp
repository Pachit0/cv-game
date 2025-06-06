#include "structures.h"

Structures::Structures() {
	image = LoadImage(RESOURCES_PATH "The Fan-tasy Tileset/Art/Buildings/House_Hay_Stone_1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	house = LoadTextureFromImage(image);
	UnloadImage(image);
}

Structures::~Structures() {
	UnloadTexture(house);
}

void Structures::drawStructures() const {
	DrawTexture(house, groundMap[10][0].x, groundMap[0][4].y, WHITE);
}