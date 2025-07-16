#include "props.h"

Props::Props(const float& TileSize, const float& Scale, const std::array<std::array<Rectangle, 30>, 60>& groundMap)
	: m_TileSize(TileSize), m_Scale(Scale), m_GroundMap(groundMap)	{
	m_PropsCoords.resize(3);
	m_PropsCoords[Scene::Level::village].resize(2);
	m_PropsCoords[Scene::Level::village][first].reserve(10);
	m_PropsCoords[Scene::Level::village][second].reserve(10);

	m_PropsCoords[Scene::Level::insideHouse].resize(2);
	m_PropsCoords[Scene::Level::insideHouse][first].reserve(1);
	m_PropsCoords[Scene::Level::insideHouse][second].reserve(1);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Bulletin_Board.png");
	ImageResize(&m_Image, (m_Image.width + 4) * m_Scale, m_Image.height * m_Scale);
	m_Board = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Buildings/House_Hay_Stone_1.png");
	ImageResize(&m_Image, (m_Image.width - 6) * m_Scale, m_Image.height * m_Scale);
	m_House = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Fireplace_1.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_Campfire = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Table_2.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_Table = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_1.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_Tree = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Chopped_Tree_1.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_CutTree = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_2.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_TreeRiver = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_3.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	m_Tree3 = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/5-ontable.png");
	m_Book = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/telescope.png");
	m_Telescope = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Lamp_1.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
	for (int i = 0; i < 4; i++) {
		m_Lamp[i] = LoadTextureFromImage(m_Image);
		ImageFlipHorizontal(&m_Image);
	}
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/chair.png");
	ImageResize(&m_Image, m_Image.width * m_Scale, m_Image.height * m_Scale);
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

void Props::drawLayer1(Scene::Level currentLevel) const {
	switch (currentLevel) {
	case Scene::Level::village: {
		DrawTexture(m_Board, m_GroundMap[35][0].x, m_GroundMap[0][12].y, WHITE);
		DrawTexture(m_House, m_GroundMap[29][0].x + 4, m_GroundMap[0][9].y, WHITE);
		DrawTexture(m_Campfire, m_GroundMap[42][0].x + 4, m_GroundMap[0][12].y + 12, WHITE);
		DrawTexture(m_Table, m_GroundMap[19][0].x + 12, m_GroundMap[0][13].y - 12, WHITE);
		DrawTexture(m_Tree, m_GroundMap[24][0].x, m_GroundMap[0][10].y, WHITE);
		DrawTexture(m_CutTree, m_GroundMap[39][0].x, m_GroundMap[0][15].y, WHITE);
		DrawTexture(m_TreeRiver, m_GroundMap[25][0].x, m_GroundMap[0][3].y, WHITE);
		DrawTexture(m_Telescope, m_GroundMap[40][0].x, m_GroundMap[0][3].y, WHITE);
		DrawTexture(m_Tree3, m_GroundMap[47][0].x, m_GroundMap[0][9].y, WHITE);
		DrawTexture(m_Book, m_GroundMap[20][0].x, m_GroundMap[0][13].y + m_TileSize, WHITE);
		break;
	}
	case Scene::Level::insideHouse: {
		DrawTexture(m_InsideChair, m_GroundMap[37][0].x - m_TileSize, m_GroundMap[0][12].y - 20, WHITE);
		break;
	}
	}

	if (IsKeyDown(KEY_G)) {
		for (const Rectangle& info : m_PropsCoords[currentLevel][first]) {
			DrawRectangleLines(info.x + m_TileSize * m_Scale, info.y + (2 * m_TileSize) * m_Scale, info.width, info.height, RED);
		}
		for (const Rectangle& info : m_PropsCoords[currentLevel][second]) {
			DrawRectangleLines(info.x + m_TileSize * m_Scale, info.y + (2 * m_TileSize) * m_Scale, info.width, info.height, GREEN);
		}
	}
}

void Props::drawLayer2(Scene::Level currentLevel) const {
	DrawTexture(m_Lamp[0], m_GroundMap[27][0].x + 4, m_GroundMap[0][15].y, WHITE);
	DrawTexture(m_Lamp[1], m_GroundMap[35][0].x + 4, m_GroundMap[0][15].y, WHITE);
	DrawTexture(m_Lamp[2], m_GroundMap[48][0].x + 4, m_GroundMap[0][13].y, WHITE);
	DrawTexture(m_Lamp[3], m_GroundMap[13][0].x, m_GroundMap[0][10].y, WHITE);
}

bool Props::underCheck(const Vector2& pos, const std::vector<Rectangle>& propsCoords) {
	for (const Rectangle& p : propsCoords) {
		if (CheckCollisionPointRec(pos, p)) {
			return true;
		}
	}
	return false;
}

std::vector<Rectangle>& Props::getCoordsLayer1(Scene::Level currentLevel) {
	return m_PropsCoords[currentLevel][first];
}

std::vector<Rectangle>& Props::getCoordsLayer2(Scene::Level currentLevel) {
	return m_PropsCoords[currentLevel][second];
}

std::vector<Props::propEntry> Props::loadPropsFromJSON(const std::string& filename)
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
		levelIndex = (entry.Level == "village") ? Scene::Level::village : Scene::Level::insideHouse;
		layerIndex = (entry.Layer == "first") ? first : second;

		float x = m_GroundMap[entry.TileX][0].x;
		float y = m_GroundMap[0][entry.TileY].y;
		float width = entry.WidthTile * m_TileSize * m_Scale;
		float height = entry.HeightTile * m_TileSize * m_Scale;

		Rectangle rect = { x, y, width, height };
		m_PropsCoords[levelIndex][layerIndex].push_back(rect);
	}
}
