#pragma once
#include "core.h"
#include "game_enums.h"

class Physics {
private:
    const float m_TileSize;
    const float m_Scale;

    int m_LevelIndex;
    const int m_ObstaclesLevelCount;
    const int m_ObstaclesCountVillage;
    const int m_ObstaclesCountHouse;

    std::unordered_map<std::string, int> m_LevelMap;
    std::vector<std::vector<Rectangle>> m_ObstaclesPerLevel;
    nlohmann::json m_Data;
    std::ifstream m_File;

public:

    Physics(const std::string& filename, const float& TileSize, const float& Scale, const std::array<std::array<Rectangle, 30>, 60>& groundMap);
    ~Physics();

    void draw(Scene::Level currentLevel);
	Vector2 collisionObjectWall(const Vector2& Pos, Vector2 velocity, const float& deltaTime, Scene::Level currentLevel);

private:

    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;

};