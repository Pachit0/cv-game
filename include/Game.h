#pragma once
#include "Core.h"
#include "player.h"
#include "tilemap.h"
#include "props.h"
#include "physics.h"
#include "Triggers.h"
#include "Camera.h"
#include "mouse.h"
#include "structures.h"

class Game {
public:
	Player player = Player();
	Tilemap tilemap = Tilemap();
	Camera_c camera_c = Camera_c();
	Physics collisions = Physics();
	Triggers triggers = Triggers();
	handleMouse mouse = handleMouse();
	Props props = Props();
	Structures structures = Structures();
	UIManager ui;

	void Update(float deltaTime) {
		triggers.update(deltaTime);
		triggers.collisionTrigger(player.getPos(), [&](Vector2 newPos) {player.setPos(newPos); });
		if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
			camera_c.update(player.getPos());
			player.handleCurrentDirection();
			player.inputHandling();
			player.setVelocity(collisions.collisionObjectWall(player.getPos(), player.getVelocity(), deltaTime));
			player.Update(deltaTime);
		}
		tilemap.update();
		mouse.update(camera_c.getCamera());
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
		}
		else {
			props.drawLayer2();
		}

	}

	void Draw() {
		switch (currentLevel) {
		case village: {
			if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
				ClearBackground(WHITE);
				tilemap.draw();
				playerDrawPriorityLayer1(); // fix it - done!
				playerDrawPriorityLayer2();
				tilemap.drawTrees();
				collisions.draw();
				}
			break;
			}
		case insideHouse: {
			if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
				ClearBackground(BLACK);
				tilemap.drawInsideHouse();
				collisions.draw();
				player.Draw();
				props.drawLayer1();
				}
			break;
			}
		}
		triggers.draw(player.getPos(), camera_c.getCamera().target);
		tilemap.debugLines();	//press C
		mouse.draw();
	}
};