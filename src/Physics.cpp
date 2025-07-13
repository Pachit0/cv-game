#include "physics.h"

Physics::Physics(const std::string& filename) : m_LevelIndex(0),
												m_X(0),
												m_Y(0),
												m_Width(0),
												m_Height(0) {

	m_File.open(filename);

	if (!m_File.is_open()) {
		std::cerr << "failed to open file!" << std::endl;
	}

	m_File >> m_Data;

	m_LevelMap = {
		{"village", Scene::Level::village},
		{"insideHouse", Scene::Level::insideHouse}
	};

	m_ObstaclesPerLevel.resize(3);
	m_ObstaclesPerLevel[Scene::Level::village].reserve(50);
	m_ObstaclesPerLevel[Scene::Level::insideHouse].reserve(10);

	for (const auto& [levelName, items] : m_Data.items()) {
		auto it = m_LevelMap.find(levelName);
		if (it == m_LevelMap.end()) continue;

		m_LevelIndex = it->second;

		for (const auto& item : items) {
			m_X = groundMap[item["x"]][0].x;
			m_Y = groundMap[0][item["y"]].y;

			if (item.contains("offsetX")) m_X += item["offsetX"];
			if (item.contains("offsetY")) m_Y += item["offsetY"];

			m_Width = item["w"] * (tileSize * scale);
			m_Height = item["h"] * (tileSize * scale);

			if (item.contains("shrink")) {
				m_Width = item["w"] * ((tileSize - item["shrink"]) * scale);
				m_Height = item["h"] * ((tileSize - item["shrink"]) * scale);
			}
			else {
				if (item.contains("shrinkX")) m_Width = item["w"] * ((tileSize - item["shrinkX"]) * scale);
				if (item.contains("shrinkY")) m_Height = item["h"] * ((tileSize - item["shrinkY"]) * scale);
			}

			m_ObstaclesPerLevel[m_LevelIndex].emplace_back(Rectangle{ m_X, m_Y, m_Width, m_Height });
		}
	}
}

Physics::~Physics() {}

Vector2 Physics::collisionObjectWall(const Vector2& Pos, Vector2 velocity, const float& deltaTime, Scene::Level currentLevel) {
	Rectangle nextPos = { Pos.x + velocity.x * deltaTime, Pos.y + velocity.y * deltaTime, tileSize * scale, tileSize * scale };

	for (const Rectangle& obstacle : m_ObstaclesPerLevel[currentLevel]) {
		if (CheckCollisionRecs(nextPos, obstacle)) {
			if (velocity.x != 0) {
				Rectangle testX = { Pos.x + velocity.x * deltaTime, Pos.y, tileSize * scale, tileSize * scale };
				if (CheckCollisionRecs(testX, obstacle)) {
					velocity.x = 0;
				}
			}

			if (velocity.y != 0) {
				Rectangle testY = { Pos.x, Pos.y + velocity.y * deltaTime, tileSize * scale, tileSize * scale };
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
				it_Obstacle.x + tileSize * scale,
				it_Obstacle.y + (tileSize * 2) * scale,
				it_Obstacle.width,
				it_Obstacle.height,
				WHITE
			);
		}
	}
}
