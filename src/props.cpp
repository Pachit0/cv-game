#include "Props.h"

Props::Props() {
	m_PropsCoords.resize(3);
	m_PropsCoords[village].resize(2);
	m_PropsCoords[village][first].reserve(10);
	m_PropsCoords[village][second].reserve(10);

	m_PropsCoords[insideHouse].resize(2);
	m_PropsCoords[insideHouse][first].reserve(1);
	m_PropsCoords[insideHouse][second].reserve(1);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Bulletin_Board.png");
	ImageResize(&m_Image, (m_Image.width + 4) * scale, m_Image.height * scale);
	m_Board = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Buildings/House_Hay_Stone_1.png");
	ImageResize(&m_Image, (m_Image.width - 6) * scale, m_Image.height * scale);
	m_House = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Fireplace_1.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_Campfire = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Table_2.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_Table = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_1.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_Tree = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Chopped_Tree_1.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_CutTree = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_2.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_TreeRiver = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_3.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_Tree3 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/5-ontable.png");
	m_Book = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/telescope.png");
	m_Telescope = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Lamp_1.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	for (int i = 0; i < 4; i++) {
		m_Lamp[i] = LoadTextureFromImage(m_Image);
		ImageFlipHorizontal(&m_Image);
	}
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/chair.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_InsideChair = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);
}

Props::~Props() {
	UnloadTexture(m_Board);
	UnloadTexture(m_House);
	UnloadTexture(m_Campfire);
	UnloadTexture(m_Table);
	UnloadTexture(m_Tree);
	UnloadTexture(m_CutTree);
	UnloadTexture(m_TreeRiver);
	UnloadTexture(m_Tree3);
	UnloadTexture(m_InsideChair);
	UnloadTexture(m_Telescope);
	for (int i = 0; i < 4; i++) {
		UnloadTexture(m_Lamp[i]);
	}
}

void Props::drawLayer1() const {
	switch (currentLevel) {
	case village: {
		DrawTexture(m_Board, groundMap[35][0].x, groundMap[0][12].y, WHITE);
		DrawTexture(m_House, groundMap[29][0].x + 4, groundMap[0][9].y, WHITE);
		DrawTexture(m_Campfire, groundMap[42][0].x + 4, groundMap[0][12].y + 12, WHITE);
		DrawTexture(m_Table, groundMap[19][0].x + 12, groundMap[0][13].y - 12, WHITE);
		DrawTexture(m_Tree, groundMap[24][0].x, groundMap[0][10].y, WHITE);
		DrawTexture(m_CutTree, groundMap[39][0].x, groundMap[0][15].y, WHITE);
		DrawTexture(m_TreeRiver, groundMap[25][0].x, groundMap[0][3].y, WHITE);
		DrawTexture(m_Telescope, groundMap[40][0].x, groundMap[0][3].y, WHITE);
		DrawTexture(m_Tree3, groundMap[47][0].x, groundMap[0][9].y, WHITE);
		DrawTexture(m_Book, groundMap[20][0].x, groundMap[0][13].y + tileSize, WHITE);
		break;
	}
	case insideHouse: {
		DrawTexture(m_InsideChair, groundMap[37][0].x - tileSize, groundMap[0][12].y - 20, WHITE);
		break;
	}
	}

	if (IsKeyDown(KEY_G)) {
		for (const Rectangle& info : m_PropsCoords[currentLevel][first]) {
			DrawRectangleLines(info.x + tileSize * scale, info.y + (2 * tileSize) * scale, info.width, info.height, RED);
		}
		for (const Rectangle& info : m_PropsCoords[currentLevel][second]) {
			DrawRectangleLines(info.x + tileSize * scale, info.y + (2 * tileSize) * scale, info.width, info.height, GREEN);
		}
	}
}

void Props::drawLayer2() const {
	DrawTexture(m_Lamp[0], groundMap[27][0].x + 4, groundMap[0][15].y, WHITE);
	DrawTexture(m_Lamp[1], groundMap[35][0].x + 4, groundMap[0][15].y, WHITE);
	DrawTexture(m_Lamp[2], groundMap[48][0].x + 4, groundMap[0][13].y, WHITE);
	DrawTexture(m_Lamp[3], groundMap[13][0].x, groundMap[0][10].y, WHITE);
}

bool Props::underCheck(const Vector2& pos, const std::vector<Rectangle>& propsCoords) {
	for (const Rectangle& p : propsCoords) {
		if (CheckCollisionPointRec(pos, p)) {
			return true;
		}
	}
	return false;
}

std::vector<Rectangle>& Props::getCoordsLayer1() {
	return m_PropsCoords[currentLevel][first];
}

std::vector<Rectangle>& Props::getCoordsLayer2() {
	return m_PropsCoords[currentLevel][second];
}

std::vector<propEntry> Props::loadPropsFromJSON(const std::string& filename)
{
	m_File.open(filename);
	if (!m_File.is_open()) {
		std::cerr << "file couldn't open" << std::endl;
	}

	m_File >> m_Data;

	for (const auto& item : m_Data) {
		m_AllProps.push_back({
			item["level"],
			item["layer"],
			item["tileX"],
			item["tileY"],
			item["widthInTiles"],
			item["heightInTiles"] });
	}

	return m_AllProps;
}

void Props::loadPropsCoordsFromJSON(const std::string& path)
{
	auto propEntries = loadPropsFromJSON(path);
	int levelIndex = 0;
	int layerIndex = 0;
	for (const auto& entry : propEntries) {
		levelIndex = (entry.Level == "village") ? village : insideHouse;
		layerIndex = (entry.Layer == "first") ? first : second;

		float x = groundMap[entry.TileX][0].x;
		float y = groundMap[0][entry.TileY].y;
		float width = entry.WidthTile * tileSize * scale;
		float height = entry.HeightTile * tileSize * scale;

		Rectangle rect = { x, y, width, height };
		m_PropsCoords[levelIndex][layerIndex].push_back(rect);
	}
}
