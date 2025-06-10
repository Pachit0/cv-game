#pragma once
#include "raylib.h"
#include "cmath"

enum mapLevel {
	village,
	insideHouse
};

extern Rectangle groundMap[60][30];

const int screenHeight = 720;
const int screenWidth = 1280;

const int baseHeight = 225;
const int baseWidth = 400;

const int mapHeight_Width = 2520;

const float scale = fmin(screenWidth / baseWidth, screenHeight / baseHeight);

const float tileSize = 16.0f;

extern int currentLevel;