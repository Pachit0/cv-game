#include "Game.h"


Game::Game() : deltaTime(0.0f),
			   isPlaying(false)
{
	init();
	ui->Init();
	props->loadPropsCoordsFromJSON(RESOURCES_PATH "props.json");
}

Game::~Game()
{
	unload();
}

void Game::update()
{
	deltaTime = GetFrameTime();

	triggers->update(deltaTime);
	triggers->collisionTrigger(player->getPos(), [&](Vector2 newPos) {player->setPos(newPos); });
	if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
		camera_c.update(player->getPos());
		player->handleCurrentDirection();
		player->inputHandling();
		player->setVelocity(collisions->collisionObjectWall(player->getPos(), player->getVelocity(), deltaTime));
		player->Update(deltaTime);
	}
	tilemap->update();
	mouse.update(camera_c.getCamera());
}

void Game::draw()
{
	if (isPlaying) {
		BeginMode2D(camera_c.getCamera());
		switch (currentLevel) {
		case village: {
			if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
				ClearBackground(WHITE);
				tilemap->draw();
				playerDrawPriorityLayer1();
				playerDrawPriorityLayer2();
				tilemap->drawTrees();
				collisions->draw();
			}
			break;
		}
		case insideHouse: {
			if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
				ClearBackground(BLACK);
				tilemap->drawInsideHouse();
				collisions->draw();
				player->Draw();
				props->drawLayer1();
				}
			break;
			}
		}
		triggers->draw(player->getPos(), camera_c.getCamera().target);
		tilemap->debugLines();	//press C
		mouse.draw();
		EndMode2D();
	}
}

void Game::init()
{
	InitWindow(screenWidth, screenHeight, "CV game");
	SetTargetFPS(60);
	player = new Player();
	if (!player) {
		std::cerr << "player couldn't load!" << std::endl;
	}
	tilemap = new Tilemap();
	if (!tilemap) {
		std::cerr << "tilemap couldn't load!" << std::endl;
	}
	camera_c = Camera_c();
	collisions = new Physics(RESOURCES_PATH "obstacles.json");
	if (!collisions) {
		std::cerr << "collisions couldn't load!" << std::endl;
	}
	triggers = new Triggers();
	if (!triggers) {
		std::cerr << "triggers couldn't load!" << std::endl;
	}
	mouse = handleMouse();
	props = new Props();
	if (!props) {
		std::cerr << "props couldn't load!" << std::endl;
	}
	ui = new UIManager();
	if (!ui) {
		std::cerr << "ui couldn't load!" << std::endl;
	}
}

void Game::unload()
{
	ui->Shutdown();
	CloseWindow();
}

void Game::run() {
	while (!WindowShouldClose()) {
		update();
		BeginDrawing();
		ui->Begin();
		if (!isPlaying) {
			ui->RenderMainMenu(isPlaying, screenWidth, screenHeight);
		}
		ui->End();
		draw();
		EndDrawing();
	}
}

void Game::playerDrawPriorityLayer1() {

	if (props->underCheck(player->getPos(), props->getCoordsLayer1())) {
		props->drawLayer1();
		player->Draw();
	}
	else {
		player->Draw();
		props->drawLayer1();
	}
}

void Game::playerDrawPriorityLayer2() {

	if (props->underCheck(player->getPos(), props->getCoordsLayer2())) {
		props->drawLayer2();
		player->Draw();
	}
	else {
		props->drawLayer2();
	}

}