#pragma once
#include "Core.h"

class Physics {
private:
	std::unordered_map<std::string, int> levelMap;
	std::vector<std::vector<Rectangle>> obstaclesLevel;
	int levelIndex;
	nlohmann::json data;
	std::ifstream file;

public:
	Physics(const std::string& filename);
	~Physics();
	void draw();
	Vector2 collisionObjectWall(const Vector2& Pos, Vector2 velocity, const float& deltaTime);
};