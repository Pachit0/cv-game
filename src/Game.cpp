#include "Game.h"

Game::Game() : m_DeltaTime(0.0f),
			   m_IsPlaying(false),
			   m_ScreenHeight(720),
			   m_ScreenWidth(1280),
			   m_BaseHeight(225),
			   m_BaseWidth(400),
			   m_Scale(3),
			   m_TileSize(16.0f)		   
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
			m_UI->RenderMainMenu(m_IsPlaying, m_ScreenWidth, m_ScreenHeight);
		}
		m_UI->End();
		draw();
		EndDrawing();
	}
}

void Game::update()
{
	m_DeltaTime = GetFrameTime();

	m_Triggers->update(m_Player->getEntityPosition(),
								[&](Vector2 newPos) {m_Player->setEntityPosition(newPos); },
								m_SceneManager.getCurrentLevel(),
								[&](Scene::Level changeLevel) {m_SceneManager.setCurrentLevel(changeLevel); },
								[&](Scene::FadeState changeFade) {m_SceneManager.setCurrentFadeState(changeFade); });
	m_SceneManager.update(m_DeltaTime);
	if (m_SceneManager.getCurrentFadeState() == Scene::FadeState::FADE_NONE || 
		m_SceneManager.getCurrentFadeState() == Scene::FadeState::FADE_OUT) 
	{
		m_MainCamera->update(m_Player->getEntityPosition(), m_SceneManager.getCurrentLevel());
		m_Player->handleCurrentDirection();
		m_Player->inputHandling();
		m_Player->setEntityVelocity(m_Physics->collisionObjectWall(m_Player->getEntityPosition(), m_Player->getEntityVelocity(), m_DeltaTime, m_SceneManager.getCurrentLevel()));
		m_Player->update(m_DeltaTime);
	}
	m_Mouse->update(m_MainCamera->getCamera());
}

void Game::draw()
{
	if (m_IsPlaying) {
		BeginMode2D(m_MainCamera->getCamera());
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
				m_Player->draw();
				m_Props->drawLayer1(m_SceneManager.getCurrentLevel());
				}
			break;
			}
		}
		m_Triggers->draw(m_Player->getEntityPosition(), m_MainCamera->getCamera().target, m_SceneManager.getCurrentLevel(),m_SceneManager.getCurrentFadeState());
		m_SceneManager.draw();
		m_Tilemap->debugLines();
		m_Mouse->draw();
		EndMode2D();
	}
}

void Game::init()
{
	InitWindow(m_ScreenWidth, m_ScreenHeight, "CV game");
	SetTargetFPS(60);

	m_Player = std::make_unique<Player>(m_Scale, m_TileSize);
	m_Tilemap = std::make_unique<Tilemap>(m_TileSize, m_Scale, m_BaseWidth, m_BaseHeight);
	m_Physics = std::make_unique<Physics>(RESOURCES_PATH "obstacles.json", m_TileSize, m_Scale, m_Tilemap->getTileMap());
	m_Triggers = std::make_unique<Triggers>(m_TileSize,m_Scale,m_ScreenWidth,m_ScreenHeight, m_Tilemap->getTileMap());
	m_Props = std::make_unique<Props>(m_TileSize, m_Scale, m_Tilemap->getTileMap());
	m_UI = std::make_unique<UIManager>();
	m_MainCamera = std::make_unique<MainCamera>(m_ScreenWidth, m_ScreenHeight);
	m_Mouse = std::make_unique<HandleMouse>(m_TileSize, m_Scale);
	m_SceneManager = SceneManager();
}

void Game::unload()
{
	m_UI->Shutdown();
	CloseWindow();
}

void Game::playerDrawPriorityLayer1() {

	if (m_Props->underCheck(m_Player->getEntityPosition(), m_Props->getCoordsLayer1(m_SceneManager.getCurrentLevel()))) {
		m_Props->drawLayer1(m_SceneManager.getCurrentLevel());
		m_Player->draw();
	}
	else {
		m_Player->draw();
		m_Props->drawLayer1(m_SceneManager.getCurrentLevel());
	}
}

void Game::playerDrawPriorityLayer2() {

	if (m_Props->underCheck(m_Player->getEntityPosition(), m_Props->getCoordsLayer2(m_SceneManager.getCurrentLevel()))) {
		m_Props->drawLayer2(m_SceneManager.getCurrentLevel());
		m_Player->draw();
	}
	else {
		m_Props->drawLayer2(m_SceneManager.getCurrentLevel());
	}

}