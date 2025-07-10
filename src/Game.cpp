#include "Game.h"


Game::Game() : m_DeltaTime(0.0f),
			   m_IsPlaying(false)
{
	init();
	m_UI->Init();
	m_Props->loadPropsCoordsFromJSON(RESOURCES_PATH "props.json");
}

Game::~Game()
{
	unload();
}

void Game::run() {
	while (!WindowShouldClose()) {
		update();
		BeginDrawing();
		m_UI->Begin();
		if (!m_IsPlaying) {
			m_UI->RenderMainMenu(m_IsPlaying, screenWidth, screenHeight);
		}
		m_UI->End();
		draw();
		EndDrawing();
	}
}

void Game::update()
{
	m_DeltaTime = GetFrameTime();

	m_Triggers->update(m_DeltaTime);
	m_Triggers->collisionTrigger(m_Player->getPos(), [&](Vector2 newPos) {m_Player->setPos(newPos); });
	if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
		m_MainCamera.update(m_Player->getPos());
		m_Player->handleCurrentDirection();
		m_Player->inputHandling();
		m_Player->setVelocity(m_Physics->collisionObjectWall(m_Player->getPos(), m_Player->getVelocity(), m_DeltaTime));
		m_Player->Update(m_DeltaTime);
	}
	m_Tilemap->update();
	m_Mouse.update(m_MainCamera.getCamera());
}

void Game::draw()
{
	if (m_IsPlaying) {
		BeginMode2D(m_MainCamera.getCamera());
		switch (currentLevel) {
		case village: {
			if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
				ClearBackground(WHITE);
				m_Tilemap->draw();
				playerDrawPriorityLayer1();
				playerDrawPriorityLayer2();
				m_Tilemap->drawTrees();
				m_Physics->draw();
			}
			break;
		}
		case insideHouse: {
			if (fadeState == FADE_NONE || fadeState == FADE_OUT) {
				ClearBackground(BLACK);
				m_Tilemap->drawInsideHouse();
				m_Physics->draw();
				m_Player->Draw();
				m_Props->drawLayer1();
				}
			break;
			}
		}
		m_Triggers->draw(m_Player->getPos(), m_MainCamera.getCamera().target);
		m_Tilemap->debugLines();	//press C
		m_Mouse.draw();
		EndMode2D();
	}
}

void Game::init()
{
	InitWindow(screenWidth, screenHeight, "CV game");
	SetTargetFPS(60);
	m_Player = new Player();
	if (!m_Player) {
		std::cerr << "m_Player couldn't load!" << std::endl;
	}
	m_Tilemap = new Tilemap();
	if (!m_Tilemap) {
		std::cerr << "m_Tilemap couldn't load!" << std::endl;
	}
	m_MainCamera = MainCamera();
	m_Physics = new Physics(RESOURCES_PATH "obstacles.json");
	if (!m_Physics) {
		std::cerr << "m_Physics couldn't load!" << std::endl;
	}
	m_Triggers = new Triggers();
	if (!m_Triggers) {
		std::cerr << "triggers couldn't load!" << std::endl;
	}
	m_Mouse = HandleMouse();
	m_Props = new Props();
	if (!m_Props) {
		std::cerr << "props couldn't load!" << std::endl;
	}
	m_UI = new UIManager();
	if (!m_UI) {
		std::cerr << "ui couldn't load!" << std::endl;
	}
}

void Game::unload()
{
	free(m_Player);
	free(m_Tilemap);
	free(m_Physics);
	free(m_Triggers);
	free(m_Props);
	free(m_UI);
	m_UI->Shutdown();
	CloseWindow();
}

void Game::playerDrawPriorityLayer1() {

	if (m_Props->underCheck(m_Player->getPos(), m_Props->getCoordsLayer1())) {
		m_Props->drawLayer1();
		m_Player->Draw();
	}
	else {
		m_Player->Draw();
		m_Props->drawLayer1();
	}
}

void Game::playerDrawPriorityLayer2() {

	if (m_Props->underCheck(m_Player->getPos(), m_Props->getCoordsLayer2())) {
		m_Props->drawLayer2();
		m_Player->Draw();
	}
	else {
		m_Props->drawLayer2();
	}

}