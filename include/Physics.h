#pragma once
#include "Core.h"
#include "gameEnums.h"

class Physics {
private:

    int m_LevelIndex;
    std::unordered_map<std::string, int> m_LevelMap;
    std::vector<std::vector<Rectangle>> m_ObstaclesPerLevel;
    nlohmann::json m_Data;
    std::ifstream m_File;

public:

    Physics(const std::string& filename);
    ~Physics();

    void draw(Scene::Level currentLevel);
	Vector2 collisionObjectWall(const Vector2& Pos, Vector2 velocity, const float& deltaTime, Scene::Level currentLevel);

private:

    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;

};