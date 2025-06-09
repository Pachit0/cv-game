#include "Props.h"

Props::Props() {
	image = LoadImage(RESOURCES_PATH "The Fan-tasy Tileset/Art/Props/Bulletin_Board.png");
	ImageResize(&image, (image.width + 4) * scale, image.height * scale);
	board = LoadTextureFromImage(image);
	UnloadImage(image);
	
	image = LoadImage(RESOURCES_PATH "The Fan-tasy Tileset/Art/Buildings/House_Hay_Stone_1.png");
	ImageResize(&image, (image.width-6) * scale, image.height * scale);
	house = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Fireplace_1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	campfire = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Table_2.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	table = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	tree = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Chopped_Tree_1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	cutTree = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_2.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	treeRiver = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_3.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	tree3 = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "The Fan-tasy Tileset/Art/Props/Lamp_1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	for (int i = 0; i < 4; i++) {
		lamp[i] = LoadTextureFromImage(image);
		ImageFlipHorizontal(&image);
	}
	UnloadImage(image);

	propsCoordsLayer1.reserve(10);
	propsCoordsLayer2.reserve(10);

	propsCoordsLayer1.emplace_back(Rectangle{ groundMap[33][0].x, groundMap[0][12].y,(tileSize * scale) * 4,(tileSize * scale) * 2 });
	propsCoordsLayer1.emplace_back(Rectangle{ groundMap[27][0].x, groundMap[0][12].y, 6 * ((tileSize) * scale), 2 * ((tileSize) * scale) });
	propsCoordsLayer1.emplace_back(Rectangle{ groundMap[40][0].x, groundMap[0][11].y, 3 * ((tileSize) * scale), 2 * ((tileSize) * scale) });
	propsCoordsLayer1.emplace_back(Rectangle{ groundMap[17][0].x, groundMap[0][12].y, 4 * ((tileSize)*scale), 2 * ((tileSize)*scale) });
	propsCoordsLayer1.emplace_back(Rectangle{ groundMap[37][0].x, groundMap[0][14].y, 3 * ((tileSize)*scale), 2 * ((tileSize)*scale) });
	propsCoordsLayer1.emplace_back(Rectangle{ groundMap[24][0].x, groundMap[0][4].y, 3 * ((tileSize)*scale), 2 * ((tileSize)*scale) });
	propsCoordsLayer1.emplace_back(Rectangle{ groundMap[45][0].x, groundMap[0][12].y , 3 * (tileSize) * scale, 2 * (tileSize) * scale });

	propsCoordsLayer2.emplace_back(Rectangle{ groundMap[25][0].x, groundMap[0][16].y, 3 * ((tileSize) * scale), 2 * ((tileSize) * scale) });
	propsCoordsLayer2.emplace_back(Rectangle{ groundMap[34][0].x, groundMap[0][16].y, 3 * ((tileSize) * scale), 2 * ((tileSize) * scale) });
	propsCoordsLayer2.emplace_back(Rectangle{ groundMap[12][0].x, groundMap[0][11].y, 3 * ((tileSize)*scale), 2 * ((tileSize)*scale) });
	propsCoordsLayer2.emplace_back(Rectangle{ groundMap[46][0].x, groundMap[0][14].y, 3 * ((tileSize)*scale), 2 * ((tileSize)*scale) });
}

Props::~Props() {
	UnloadTexture(board);
	UnloadTexture(house);
	UnloadTexture(campfire);
	UnloadTexture(table);
	UnloadTexture(tree);
	UnloadTexture(cutTree);
	UnloadTexture(treeRiver);
	UnloadTexture(tree3);
	for (int i = 0; i < 4; i++) {
		UnloadTexture(lamp[i]);
	}
}

void Props::drawLayer1() const {
	DrawTexture(board, groundMap[35][0].x, groundMap[0][12].y, WHITE);
	DrawTexture(house, groundMap[29][0].x + 4, groundMap[0][9].y, WHITE);
	DrawTexture(campfire, groundMap[42][0].x + 4, groundMap[0][12].y + 12, WHITE);
	DrawTexture(table, groundMap[19][0].x + 12, groundMap[0][13].y - 12, WHITE);
	DrawTexture(tree, groundMap[24][0].x, groundMap[0][10].y, WHITE);
	DrawTexture(cutTree, groundMap[39][0].x, groundMap[0][15].y, WHITE);
	DrawTexture(treeRiver, groundMap[25][0].x, groundMap[0][3].y, WHITE);
	DrawTexture(tree3, groundMap[47][0].x, groundMap[0][9].y, WHITE);

	if (IsKeyDown(KEY_G)) {
		for (const Rectangle& info : propsCoordsLayer1) {
			DrawRectangleLines(info.x + tileSize * scale, info.y + (2 * tileSize) * scale, info.width, info.height, RED);
		}
		for (const Rectangle& info : propsCoordsLayer2) {
			DrawRectangleLines(info.x + tileSize * scale, info.y + (2 * tileSize) * scale, info.width, info.height, GREEN);
		}
	}
}

void Props::drawLayer2() const {
	DrawTexture(lamp[0], groundMap[27][0].x + 4, groundMap[0][15].y, WHITE);
	DrawTexture(lamp[1], groundMap[35][0].x + 4, groundMap[0][15].y, WHITE);
	DrawTexture(lamp[2], groundMap[48][0].x + 4, groundMap[0][13].y, WHITE);
	DrawTexture(lamp[3], groundMap[13][0].x, groundMap[0][10].y, WHITE);
}

bool Props::underCheck(const Vector2& pos, const std::vector<Rectangle>& propsCoords) {
	for (const Rectangle& p : propsCoords ) {
		if (CheckCollisionPointRec(pos, p)) {
			return 1;
		}
	}
	return 0;
}
// Make it better, just make it better
std::vector<Rectangle>& Props::getCoordsLayer1() {
	return propsCoordsLayer1;
}

std::vector<Rectangle>& Props::getCoordsLayer2() {
	return propsCoordsLayer2;
}