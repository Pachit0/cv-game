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

	m_Image = LoadImage(RESOURCES_PATH "Map/TileSetImages/Props/Lamp_1.png");
	for (int i = 0; i < 4; i++) {
		m_Lamp[i] = LoadTextureFromImage(m_Image);
		SetTextureFilter(m_Lamp[i], TEXTURE_FILTER_POINT);
		ImageFlipHorizontal(&m_Image);
	}
	UnloadImage(m_Image);

	m_TextureMapID[BOARD] = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Props/Bulletin_Board.png");
	m_TextureMapID[HOUSE] = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Buildings/House_Hay_Stone_1.png");
	m_TextureMapID[CAMPFIRE] = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Props/Fireplace_1.png");
	m_TextureMapID[TABLE] = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Props/Table_2.png");
	m_TextureMapID[TREE] = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_1.png");
	m_TextureMapID[CUT_TREE] = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Props/Chopped_Tree_1.png");
	m_TextureMapID[TREE_RIVER] = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_2.png");
	m_TextureMapID[TREE_3] = LoadFilteredTexture(RESOURCES_PATH "Map/TileSetImages/Trees and Bushes/Tree_Emerald_3.png");
	m_TextureMapID[BOOK] = LoadFilteredTexture(RESOURCES_PATH "Map/5-ontable.png");
	m_TextureMapID[TELESCOPE] = LoadFilteredTexture(RESOURCES_PATH "Map/telescope.png");
	m_TextureMapID[insideChair] = LoadFilteredTexture(RESOURCES_PATH "Map/chair.png");
	m_TextureMapID[LAMP1] = m_Lamp[0];
	m_TextureMapID[LAMP2] = m_Lamp[1];
	m_TextureMapID[LAMP3] = m_Lamp[2];
	m_TextureMapID[LAMP4] = m_Lamp[3];

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
	std::string levelStr;

	switch (currentLevel) {
	case Scene::Level::village:
		levelStr = "village";
		break;
	case Scene::Level::insideHouse:
		levelStr = "insideHouse";
		break;
	default:
		return;
	}

	auto it = m_AllPropsTextureCoords.find(levelStr);
	if (it == m_AllPropsTextureCoords.end()) return;

	auto layerIt = it->second.find(1);
	if (layerIt == it->second.end()) return;

	for (const auto& [zIndex, entries] : layerIt->second) {
		for (const auto& entry : entries) {
			auto texIt = m_TextureMapID.find(entry.texID);
			if (texIt == m_TextureMapID.end()) {
				std::cerr << "Missing texture for texID: " << entry.texID << std::endl;
				continue;
			}
			Texture2D texture = texIt->second;
			Vector2 position = {
				float(entry.drawX) * m_TileSize * m_Scale + entry.offsetX,
				float(entry.drawY) * m_TileSize * m_Scale + entry.offsetY
			};
			if (!entry.scale) {
				DrawTextureEx(texture, position, 0.0f, 1.0f, WHITE);
			}
			else {
				DrawTextureEx(texture, position, 0.0f, m_Scale, WHITE);
			}
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
	std::string levelStr;

	switch (currentLevel) {
	case Scene::Level::village:
		levelStr = "village";
		break;
	case Scene::Level::insideHouse:
		levelStr = "insideHouse";
		break;
	default:
		return;
	}

	auto it = m_AllPropsTextureCoords.find(levelStr);
	if (it == m_AllPropsTextureCoords.end()) return;

	auto layerIt = it->second.find(2);
	if (layerIt == it->second.end()) return;

	for (const auto& [zIndex, entries] : layerIt->second) {
		for (const auto& entry : entries) {
			auto texIt = m_TextureMapID.find(entry.texID);
			if (texIt == m_TextureMapID.end()) {
				std::cerr << "Missing texture for texID: " << entry.texID << std::endl;
				continue;
			}
			Texture2D texture = texIt->second;
			Vector2 position = {
				float(entry.drawX) * m_TileSize * m_Scale + entry.offsetX,
				float(entry.drawY) * m_TileSize * m_Scale + entry.offsetY
			};

			float drawScale = entry.scale ? m_Scale : 1.0f;
			DrawTextureEx(texture, position, 0.0f, drawScale, WHITE);
		}
	}
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

void Props::loadPropsTextureCoordsFromJSON(const std::string& path) {
	nlohmann::json Data;
	std::ifstream File(path);

	if (!File.is_open()) {
		std::cerr << "File failed to open: " << path << std::endl;
		return;
	}

	File >> Data;
	File.close();

	for (const auto& item : Data) {
		const std::string& level = item["currentLevel"];
		int layer = item["layer"];

		propCoordsEntry entry;
		entry.texID = item["enumType"];
		entry.drawX = item["drawPropX"];
		entry.drawY = item["drawPropY"];
		entry.scale = item["scale"];
		entry.offsetX = item.value("drawOffsetX", 0);
		entry.offsetY = item.value("drawOffsetY", 0);
		int zIndex = item.value("zIndex", 0);

		// HATEHATEHATE
		m_AllPropsTextureCoords[level][layer][zIndex].emplace_back(entry);
	}
}