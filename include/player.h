#pragma once
#include "core.h"
#include "entity_manager.h"
#include "scene_manager.h"

class Player : public Entity {
private:
	
	const float m_Scale;
	
	const float m_SpawnPosX;
	const float m_SpawnPosY;

	const float m_RectWidthPlayer;
	const float m_RectHeightPlayer;

	unsigned m_FrameNum;
	unsigned m_FrameDelay;
	unsigned m_FrameDelayCount;
	unsigned m_FrameIndex;

	Rectangle m_Movement_Rect[6][8];

	int m_Directions;

	Texture2D m_Idle;
	Texture2D m_Walk;
	Image m_Image;
public:

	enum PlayerDirection {
		DOWN,
		LEFT_DOWN,
		LEFT_UP,
		UP,
		RIGHT_UP,
		RIGHT_DOWN,
		DIR_COUNT
	};

	Player(const float& Scale, const float& TileSize);
	~Player();

	void inputHandling();
	void handleCurrentDirection();
	//void checkScenePouse(Scene::FadeState currentFadeState);
	void update(const float& deltaTime) override ;
	void draw() override;

};