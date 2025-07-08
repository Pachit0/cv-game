#pragma once

#include "player.h"
#include "tilemap.h"
#include "props.h"
#include "physics.h"
#include "Triggers.h"
#include "Camera.h"
#include "mouse.h"

class Game
{
private:
	void update();
	void draw();
	void init();
	void unload();

	Player* player;
	Tilemap* tilemap;
	Camera_c camera_c;
	Physics* collisions;
	Triggers* triggers;
	handleMouse mouse;
	Props* props;
	UIManager* ui;

	float deltaTime;
	bool isPlaying;
public:
	Game();
	~Game();

	void run();
	void playerDrawPriorityLayer1();
	void playerDrawPriorityLayer2();
};