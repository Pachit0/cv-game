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

	m_Triggers->update(m_DeltaTime, m_SceneManager.getCurrentFadeState());
	m_Triggers->collisionTrigger(m_Player->getPos(),
								[&](Vector2 newPos) {m_Player->setPos(newPos); },
								m_SceneManager.getCurrentLevel(),
								[&](Scene::Level changeLevel) {m_SceneManager.setCurrentLevel(changeLevel); },
								[&](Scene::FadeState changeFade) {m_SceneManager.setCurrentFadeState(changeFade); });

	m_SceneManager.update(m_DeltaTime);
	if (m_SceneManager.getCurrentFadeState() == Scene::FadeState::FADE_NONE || 
		m_SceneManager.getCurrentFadeState() == Scene::FadeState::FADE_OUT) 
	{
		m_MainCamera.update(m_Player->getPos(), m_SceneManager.getCurrentLevel());
		m_Player->handleCurrentDirection();
		m_Player->inputHandling();
		m_Player->setVelocity(m_Physics->collisionObjectWall(m_Player->getPos(), m_Player->getVelocity(), m_DeltaTime, m_SceneManager.getCurrentLevel()));
		m_Player->Update(m_DeltaTime);
	}
	m_Tilemap->update();
	m_Mouse.update(m_MainCamera.getCamera());
}

void Game::draw()
{
	if (m_IsPlaying) {
		BeginMode2D(m_MainCamera.getCamera());
		switch (m_SceneManager.getCurrentLevel()) {
		case Scene::Level::village: {
			if (m_SceneManager.getCurrentFadeState() == Scene::FadeState::FADE_NONE ||
				m_SceneManager.getCurrentFadeState() == Scene::FadeState::FADE_OUT) {
				ClearBackground(WHITE);
				m_Tilemap->draw();
				playerDrawPriorityLayer1();
				playerDrawPriorityLayer2();
				m_Tilemap->drawTrees();
				m_Physics->draw(m_SceneManager.getCurrentLevel());
			}
			break;
		}
		case Scene::Level::insideHouse: {
			if (m_SceneManager.getCurrentFadeState() == Scene::FadeState::FADE_NONE || 
				m_SceneManager.getCurrentFadeState() == Scene::FadeState::FADE_OUT) {
				ClearBackground(BLACK);
				m_Tilemap->drawInsideHouse();
				m_Physics->draw(m_SceneManager.getCurrentLevel());
				m_Player->Draw();
				m_Props->drawLayer1(m_SceneManager.getCurrentLevel());
				}
			break;
			}
		}
		m_Triggers->draw(m_Player->getPos(), m_MainCamera.getCamera().target, m_SceneManager.getCurrentLevel(),m_SceneManager.getCurrentFadeState());
		m_SceneManager.draw();
		m_Tilemap->debugLines();	//press C
		m_Mouse.draw();
		EndMode2D();
	}
}

void Game::init()
{
	InitWindow(screenWidth, screenHeight, "CV game");
	SetTargetFPS(60);

	m_Player = new (std::nothrow) Player();
	if (!m_Player) {
		std::cerr << "m_Player couldn't load!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	m_Tilemap = new (std::nothrow) Tilemap();
	if (!m_Tilemap) {
		std::cerr << "m_Tilemap couldn't load!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	m_MainCamera = MainCamera();

	m_Physics = new (std::nothrow) Physics(RESOURCES_PATH "obstacles.json");
	if (!m_Physics) {
		std::cerr << "m_Physics couldn't load!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	m_Triggers = new (std::nothrow) Triggers();
	if (!m_Triggers) {
		std::cerr << "triggers couldn't load!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	m_Mouse = HandleMouse();

	m_Props = new (std::nothrow) Props();
	if (!m_Props) {
		std::cerr << "props couldn't load!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	m_UI = new (std::nothrow) UIManager();
	if (!m_UI) {
		std::cerr << "ui couldn't load!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	m_SceneManager = SceneManager();
}
void Game::unload()
{
	delete(m_Player);
	delete(m_Tilemap);
	delete(m_Physics);
	delete(m_Triggers);
	delete(m_Props);
	delete(m_UI);
	m_UI->Shutdown();
	CloseWindow();
}

void Game::playerDrawPriorityLayer1() {

	if (m_Props->underCheck(m_Player->getPos(), m_Props->getCoordsLayer1(m_SceneManager.getCurrentLevel()))) {
		m_Props->drawLayer1(m_SceneManager.getCurrentLevel());
		m_Player->Draw();
	}
	else {
		m_Player->Draw();
		m_Props->drawLayer1(m_SceneManager.getCurrentLevel());
	}
}

void Game::playerDrawPriorityLayer2() {

	if (m_Props->underCheck(m_Player->getPos(), m_Props->getCoordsLayer2(m_SceneManager.getCurrentLevel()))) {
		m_Props->drawLayer2(m_SceneManager.getCurrentLevel());
		m_Player->Draw();
	}
	else {
		m_Props->drawLayer2(m_SceneManager.getCurrentLevel());
	}

}