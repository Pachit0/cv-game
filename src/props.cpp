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

	m_Board = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Props/Bulletin_Board.png");
	m_House = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Buildings/House_Hay_Stone_1.png");
	m_Campfire = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Props/Fireplace_1.png");
	m_Table = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Props/Table_2.png");
	m_Tree = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_1.png");
	m_CutTree = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Props/Chopped_Tree_1.png");
	m_TreeRiver = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_2.png");
	m_Tree3 = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_3.png");
	m_Book = LoadFilteredTexture(RESOURCES_PATH "Map/5-ontable.png");
	m_Telescope = LoadFilteredTexture(RESOURCES_PATH "Map/telescope.png");

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Lamp_1.png");
	for (int i = 0; i < 4; i++) {
		m_Lamp[i] = LoadTextureFromImage(m_Image);
		SetTextureFilter(m_Lamp[i], TEXTURE_FILTER_POINT);
		ImageFlipHorizontal(&m_Image);
	}
	UnloadImage(m_Image);

	m_InsideChair = LoadFilteredTexture(RESOURCES_PATH "Map/chair.png");
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
		DrawTextureEx(m_Board, { m_GroundMap[35][0].x, m_GroundMap[0][12].y }, 0.0f, m_Scale, WHITE);
		DrawTextureEx(m_House, { m_GroundMap[29][0].x - 4, m_GroundMap[0][9].y }, 0.0f, m_Scale, WHITE);
		DrawTextureEx(m_Campfire, { m_GroundMap[42][0].x + 4, m_GroundMap[0][13].y + 12 }, 0.0f, m_Scale, WHITE);
		DrawTextureEx(m_Table, {m_GroundMap[19][0].x + 12, m_GroundMap[0][14].y - 12}, 0.0f, m_Scale, WHITE);
		DrawTextureEx(m_Tree, { m_GroundMap[24][0].x, m_GroundMap[0][11].y }, 0.0f, m_Scale, WHITE);
		DrawTextureEx(m_CutTree, { m_GroundMap[39][0].x, m_GroundMap[0][16].y }, 0.0f, m_Scale, WHITE);
		DrawTextureEx(m_TreeRiver, { m_GroundMap[25][0].x, m_GroundMap[0][3].y }, 0.0f, m_Scale, WHITE);
		DrawTextureEx(m_Tree3, { m_GroundMap[47][0].x, m_GroundMap[0][9].y }, 0.0f, m_Scale, WHITE);
		DrawTexture(m_Book, m_GroundMap[20][0].x, m_GroundMap[0][14].y + m_TileSize, WHITE);
		DrawTexture(m_Telescope, m_GroundMap[40][0].x, m_GroundMap[0][4].y, WHITE);
		break;
	}
	case Scene::Level::insideHouse: {
		DrawTextureEx(m_InsideChair, { m_GroundMap[37][0].x - m_TileSize, m_GroundMap[0][12].y - 20 },0.0f,m_Scale, WHITE);
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
	DrawTextureEx(m_Lamp[0], { m_GroundMap[27][0].x + 4, m_GroundMap[0][15].y }, 0.0f, m_Scale, WHITE);
	DrawTextureEx(m_Lamp[1], { m_GroundMap[35][0].x + 4, m_GroundMap[0][15].y }, 0.0f, m_Scale, WHITE);
	DrawTextureEx(m_Lamp[2], { m_GroundMap[48][0].x + 4, m_GroundMap[0][13].y }, 0.0f, m_Scale, WHITE);
	DrawTextureEx(m_Lamp[3], { m_GroundMap[13][0].x, m_GroundMap[0][10].y }, 0.0f, m_Scale, WHITE);
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

void Props::loadPropsFromJSON(const std::string& filename)
{
	nlohmann::json Data;
	std::ifstream File;

	File.open(filename);
	if (!File.is_open()) {
		std::cerr << "file couldn't open" << std::endl;
	}

	File >> Data;

	for (const auto& item : Data) {
		m_AllProps.push_back({
			item["level"],
			item["layer"],
			item["tileX"],
			item["tileY"],
			item["widthInTiles"],
			item["heightInTiles"] });
	}

	File.close();
}

void Props::loadPropsCoordsFromJSON(const std::string& path)
{
	loadPropsFromJSON(path);
	int levelIndex = 0;
	int layerIndex = 0;
	for (const auto& entry : m_AllProps) {
		levelIndex = (entry.Level == "village") ? Scene::Level::village : Scene::Level::insideHouse;
		layerIndex = (entry.Layer == "first") ? first : second;

		float x = m_GroundMap[entry.TileX][0].x;
		float y = m_GroundMap[0][entry.TileY].y;
		float width = entry.WidthTile * m_TileSize * m_Scale;
		float height = entry.HeightTile * m_TileSize * m_Scale;

		Rectangle rect = { x, y, width, height };
		m_PropsCoords[levelIndex][layerIndex].emplace_back(rect);
	}
}
