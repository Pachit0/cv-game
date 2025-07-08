#include "physics.h"

Physics::Physics(const std::string& filename) : levelIndex(0) {

	file.open(filename);

	if (!file.is_open()) {
		std::cerr << "failed to open file!" << std::endl;
		return;
	}

	file >> data;

	levelMap = { {"village", village},
				 {"insideHouse", insideHouse}
	};

	obstaclesLevel.resize(3);
	obstaclesLevel[village].reserve(50);
	obstaclesLevel[insideHouse].reserve(10);

	for (const auto& [levelName, items] : data.items()) {
		auto it = levelMap.find(levelName); 
		if (it == levelMap.end()) continue; // skipping unknown maps if any (so far none)

		levelIndex = it->second; // passing the second value of levelMap

		for (const auto& item : items) {
			float x = groundMap[item["x"]][0].x;
			float y = groundMap[0][item["y"]].y;

			if (item.contains("offsetX")) x += item["offsetX"];
			if (item.contains("offsetY")) y += item["offsetY"];

			float w = item["w"] * (tileSize * scale);
			float h = item["h"] * (tileSize * scale);

			if (item.contains("shrink")) {
				w = item["w"] * ((tileSize - item["shrink"]) * scale);
				h = item["h"] * ((tileSize - item["shrink"]) * scale);
			}
			else {
				if (item.contains("shrinkX")) w = item["w"] * ((tileSize - item["shrinkX"]) * scale);
				if (item.contains("shrinkY")) h = item["h"] * ((tileSize - item["shrinkY"]) * scale);
			}

			obstaclesLevel[levelIndex].emplace_back(Rectangle{ x, y, w, h });
		}
	}
}

Physics::~Physics() {}

Vector2 Physics::collisionObjectWall(const Vector2& Pos,Vector2 velocity,const float& deltaTime) {
	
	Rectangle nextPos = { Pos.x + velocity.x * deltaTime, Pos.y + velocity.y * deltaTime, tileSize * scale, tileSize * scale };

	for (const Rectangle& obstacle : obstaclesLevel[currentLevel])
	{
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

void Physics::draw() {
	if (IsKeyDown(KEY_O)) {
		for (const Rectangle& obstacle : obstaclesLevel[currentLevel]) {
			DrawRectangleLines(obstacle.x + tileSize * scale, obstacle.y + (tileSize * 2) * scale, obstacle.width, obstacle.height, WHITE);
		}
	}
}
