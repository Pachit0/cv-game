#include "Props.h"

Props::Props() {

	propsCoords.resize(3);
	propsCoords[village].resize(2);
	propsCoords[village][first].reserve(10);
	propsCoords[village][second].reserve(10);

	propsCoords[insideHouse].resize(2);
	propsCoords[insideHouse][first].reserve(1);
	propsCoords[insideHouse][second].reserve(1);

	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Bulletin_Board.png");
	ImageResize(&image, (image.width + 4) * scale, image.height * scale);
	board = LoadTextureFromImage(image);
	UnloadImage(image);
	
	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Buildings/House_Hay_Stone_1.png");
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

	image = LoadImage(RESOURCES_PATH "Map/5-ontable.png");
	book = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/telescope.png");
	telescope = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Lamp_1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	for (int i = 0; i < 4; i++) {
		lamp[i] = LoadTextureFromImage(image);
		ImageFlipHorizontal(&image);
	}
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/chair.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	insideChair = LoadTextureFromImage(image);
	UnloadImage(image);
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
	UnloadTexture(insideChair);
	UnloadTexture(telescope);
	for (int i = 0; i < 4; i++) {
		UnloadTexture(lamp[i]);
	}
}

void Props::drawLayer1() const {
	switch (currentLevel) {
	case village: {
		DrawTexture(board, groundMap[35][0].x, groundMap[0][12].y, WHITE);
		DrawTexture(house, groundMap[29][0].x + 4, groundMap[0][9].y, WHITE);
		DrawTexture(campfire, groundMap[42][0].x + 4, groundMap[0][12].y + 12, WHITE);
		DrawTexture(table, groundMap[19][0].x + 12, groundMap[0][13].y - 12, WHITE);
		DrawTexture(tree, groundMap[24][0].x, groundMap[0][10].y, WHITE);
		DrawTexture(cutTree, groundMap[39][0].x, groundMap[0][15].y, WHITE);
		DrawTexture(treeRiver, groundMap[25][0].x, groundMap[0][3].y, WHITE);
		DrawTexture(telescope, groundMap[40][0].x, groundMap[0][3].y, WHITE);
		DrawTexture(tree3, groundMap[47][0].x, groundMap[0][9].y, WHITE);
		DrawTexture(book, groundMap[20][0].x, groundMap[0][13].y + tileSize, WHITE);
		break;
		}
	case insideHouse: {
		DrawTexture(insideChair, 1765, 555, WHITE);
		break;
		}
	}

	if (IsKeyDown(KEY_G)) {
		for (const Rectangle& info : propsCoords[currentLevel][first]) {
			DrawRectangleLines(info.x + tileSize * scale, info.y + (2 * tileSize) * scale, info.width, info.height, RED);
		}
		for (const Rectangle& info : propsCoords[currentLevel][second]) {
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
	for (const Rectangle& p : propsCoords) {
		if (CheckCollisionPointRec(pos, p)) {
			return 1;
		}
	}
	return 0;
}

std::vector<Rectangle>& Props::getCoordsLayer1() {
	return propsCoords[currentLevel][first];
}

std::vector<Rectangle>& Props::getCoordsLayer2() {
	return propsCoords[currentLevel][second];
}

std::vector<propEntry> Props::loadPropsFromJSON(const std::string& filename)
{
	file.open(filename);
	if (!file.is_open()) {
		std::cerr << "file couldn't open" << std::endl;
	}

	file >> data;

	for (const auto& item : data) {
		allProps.push_back({
			item["level"],
			item["layer"],
			item["tileX"],
			item["tileY"],
			item["widthInTiles"],
			item["heightInTiles"] });
	}

	return allProps;
}

void Props::loadPropsCoordsFromJSON(const std::string& path)
{
	auto propEntries = loadPropsFromJSON(path);
	int levelIndex = 0;
	int layerIndex = 0;
	for (const auto& entry : propEntries) {
		levelIndex = (entry.level == "village") ? village : insideHouse;
		layerIndex = (entry.layer == "first") ? first : second;

		float x = groundMap[entry.tileX][0].x;
		float y = groundMap[0][entry.tileY].y;
		float width = entry.widthTile * tileSize * scale;
		float height = entry.heightTile * tileSize * scale;

		Rectangle rect = { x, y, width, height };
		propsCoords[levelIndex][layerIndex].push_back(rect);
	}
}
