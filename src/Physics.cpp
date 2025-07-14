#include "physics.h"

Physics::Physics(const std::string& filename, const float& TileSize, const float& Scale, const std::array<std::array<Rectangle, 30>, 60>& groundMap) : m_LevelIndex(0),
												m_X(0),
												m_Y(0),
												m_Width(0),
												m_Height(0),
												m_TileSize(TileSize),
												m_Scale(Scale),
												m_ObstaclesLevelCount(3),
												m_ObstaclesCountVillage(50),
												m_ObstaclesCountHouse(10){

	m_File.open(filename);

	if (!m_File.is_open()) {
		std::cerr << "failed to open file!" << std::endl;
	}

	m_File >> m_Data;

	m_LevelMap = {
		{"village", Scene::Level::village},
		{"insideHouse", Scene::Level::insideHouse}
	};

	m_ObstaclesPerLevel.resize(m_ObstaclesLevelCount);
	m_ObstaclesPerLevel[Scene::Level::village].reserve(m_ObstaclesCountVillage);
	m_ObstaclesPerLevel[Scene::Level::insideHouse].reserve(m_ObstaclesCountHouse);

	for (const auto& [levelName, items] : m_Data.items()) {
		auto it = m_LevelMap.find(levelName);
		if (it == m_LevelMap.end()) continue;

		m_LevelIndex = it->second;

		for (const auto& item : items) {
			m_X = groundMap[item["x"]][0].x;
			m_Y = groundMap[0][item["y"]].y;

			if (item.contains("offsetX")) m_X += item["offsetX"];
			if (item.contains("offsetY")) m_Y += item["offsetY"];

			m_Width = item["w"] * (TileSize * Scale);
			m_Height = item["h"] * (TileSize * Scale);

			if (item.contains("shrink")) {
				m_Width = item["w"] * ((TileSize - item["shrink"]) * Scale);
				m_Height = item["h"] * ((TileSize - item["shrink"]) * Scale);
			}
			else {
				if (item.contains("shrinkX")) m_Width = item["w"] * ((TileSize - item["shrinkX"]) * Scale);
				if (item.contains("shrinkY")) m_Height = item["h"] * ((TileSize - item["shrinkY"]) * Scale);
			}

			m_ObstaclesPerLevel[m_LevelIndex].emplace_back(Rectangle{ m_X, m_Y, m_Width, m_Height });
		}
	}
}

Physics::~Physics() {}

Vector2 Physics::collisionObjectWall(const Vector2& Pos, Vector2 velocity, const float& deltaTime, Scene::Level currentLevel) {
	Rectangle nextPos = { Pos.x + velocity.x * deltaTime, Pos.y + velocity.y * deltaTime, m_TileSize * m_Scale, m_TileSize * m_Scale };

	for (const Rectangle& obstacle : m_ObstaclesPerLevel[currentLevel]) {
		if (CheckCollisionRecs(nextPos, obstacle)) {
			if (velocity.x != 0) {
				Rectangle testX = { Pos.x + velocity.x * deltaTime, Pos.y, m_TileSize * m_Scale, m_TileSize * m_Scale };
				if (CheckCollisionRecs(testX, obstacle)) {
					velocity.x = 0;
				}
			}

			if (velocity.y != 0) {
				Rectangle testY = { Pos.x, Pos.y + velocity.y * deltaTime, m_TileSize * m_Scale, m_TileSize * m_Scale };
				if (CheckCollisionRecs(testY, obstacle)) {
					velocity.y = 0;
				}
			}
		}
	}

	return velocity;
}

void Physics::draw(Scene::Level currentLevel) {
	if (IsKeyDown(KEY_O)) {
		for (const Rectangle& it_Obstacle : m_ObstaclesPerLevel[currentLevel]) {
			DrawRectangleLines(
				it_Obstacle.x + m_TileSize * m_Scale,
				it_Obstacle.y + (m_TileSize * 2) * m_Scale,
				it_Obstacle.width,
				it_Obstacle.height,
				WHITE
			);
		}
	}
}
