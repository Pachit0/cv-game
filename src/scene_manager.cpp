#include "scene_manager.h"

SceneManager::SceneManager() : m_CurrentLevel(Scene::Level::village),
							   m_FadeState(Scene::FadeState::FADE_NONE),
							   fadeAlpha(0.0f),
							   fadeSpeed(1.5f),
							   fadeHoldTime(0.1f),
							   fadeTimer(0.0f)	{

}

SceneManager::~SceneManager() {}

Scene::Level SceneManager::getCurrentLevel() const {
	return m_CurrentLevel;
}

void SceneManager::setCurrentLevel(Scene::Level level) {
	m_CurrentLevel = level;
}

Scene::FadeState SceneManager::getCurrentFadeState() const {
	return m_FadeState;
}
void SceneManager::setCurrentFadeState(Scene::FadeState fadeState) {
	m_FadeState = fadeState;
}

void SceneManager::draw() {
	if (m_FadeState != Scene::FADE_NONE) {
		DrawRectangle(0, 0, GetScreenWidth() * 3, GetScreenHeight() * 2, Fade(BLACK, fadeAlpha));
	}
}

void SceneManager::update(const float& deltaTime) {
	switch (m_FadeState) {
	case Scene::FADE_IN: {
		fadeAlpha += fadeSpeed * deltaTime;
		if (fadeAlpha >= 1.0f) {
			fadeAlpha = 1.0f;
			m_FadeState = Scene::FADE_HOLD;
			fadeTimer = 0.0f;
		}
		break;
	}

	case Scene::FADE_HOLD: {
		fadeTimer += deltaTime;
		if (fadeTimer >= fadeHoldTime) {
			m_FadeState = Scene::FADE_OUT;
		}
		break;
	}

	case Scene::FADE_OUT: {
		fadeAlpha -= fadeSpeed * deltaTime;
		if (fadeAlpha <= 0.0f) {
			fadeAlpha = 0.0f;
			m_FadeState = Scene::FADE_NONE;
		}
		break;
	}

	default:
		break;
	}

	if (IsKeyPressed(KEY_F)) {
		ToggleFullscreen();
	}
}