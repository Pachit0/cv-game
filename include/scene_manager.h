#pragma once
#include "core.h"
#include "game_enums.h"

class SceneManager {

public:

	SceneManager();
	~SceneManager();

	Scene::Level getCurrentLevel() const;
	void setCurrentLevel(Scene::Level level);

	Scene::FadeState getCurrentFadeState() const;
	void setCurrentFadeState(Scene::FadeState fadeState);

	void update(const float& deltaTime);
	void draw();
private:
	Scene::Level m_CurrentLevel;
	Scene::FadeState m_FadeState;

	float fadeAlpha;
	float fadeSpeed;
	float fadeHoldTime;
	float fadeTimer;
};