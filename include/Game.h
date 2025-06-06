#pragma once
#include "Core.h"
#include "player.h"
#include "tilemap.h"
#include "props.h"
#include "physics.h"
#include "Triggers.h"
#include "Camera.h"
#include "structures.h"

class Game {
public:
	Player player = Player();
	Tilemap tilemap = Tilemap();
	Camera_c camera_c = Camera_c();
	Physics collisions = Physics();
	Triggers triggers = Triggers();
	Props props = Props();
	Structures structures = Structures();
	UIManager ui;

	void Update(float deltaTime) {
		player.handleCurrentDirection();
		player.inputHandling();
		player.setVelocity(collisions.collisionObjectWall(player.getPos(), player.getVelocity(), deltaTime));
		camera_c.update(player);
		player.Update(deltaTime);
		tilemap.update(camera_c.getCamera());
		triggers.update(player.getPos());
	}

	void playerDrawPriorityLayer1() {

		if (props.underCheck(player.getPos(), props.getCoordsLayer1())) {
			props.drawLayer1();
			player.Draw();
		}
		else {
			player.Draw();
			props.drawLayer1();
		}

	}

	void playerDrawPriorityLayer2() {

		if (props.underCheck(player.getPos(), props.getCoordsLayer2())) {
			props.drawLayer2();
			player.Draw();
		} else {
			props.drawLayer2();
		}

	}

	void Draw() {
		ClearBackground(WHITE);
		tilemap.draw(player.getPos());
		tilemap.debugLines();	//press C
		playerDrawPriorityLayer1(); // fix it - done!
		playerDrawPriorityLayer2();
		tilemap.drawTrees();
		//structures.drawStructures();
		collisions.draw(player.getPos());
		triggers.draw(player.getPos());
	}
};