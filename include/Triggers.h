#pragma once
#include "Core.h"
#include "gameEnums.h"

class Triggers {
private:

	enum InteractionState {
		STATE_INACTIVE,
		STATE_PROMPT,
		STATE_ACTIVE
	};

	struct TriggerInteraction {
		InteractionState state = STATE_INACTIVE;

		void updateTrigger(const Rectangle& playerRect, const Rectangle& triggerRect) {
			if (CheckCollisionRecs(playerRect, triggerRect)) {
				if (IsKeyPressed(KEY_E)) {
					state = InteractionState::STATE_ACTIVE;
				}
				else if (IsKeyPressed(KEY_Q)) {
					state = InteractionState::STATE_INACTIVE;
				}
				else if (state == InteractionState::STATE_INACTIVE) {
					state = InteractionState::STATE_PROMPT;
				}
			}
			else {
				state = InteractionState::STATE_INACTIVE;
			}
		}

		bool isPrompting() const { return state == InteractionState::STATE_PROMPT; }
		bool isActive() const { return state == InteractionState::STATE_ACTIVE; }
	};

	TriggerInteraction m_TvTrigger;
	TriggerInteraction m_BookTrigger;
	TriggerInteraction m_TelescopeTrigger;
	TriggerInteraction m_NoteTrigger;

	bool m_EnterHousePrompt;
	bool m_ExitHousePrompt;

	int m_Frames;
	int m_CurrentAnimFrame;
	int m_FrameDelay;
	int m_FrameCounter;
	unsigned int m_NextFrameDataOffset;

	std::vector<std::vector<Rectangle>> m_TriggersLevel;

	Texture2D m_Scroll;
	Texture2D m_Paper;
	Texture2D m_E_Letter;
	Texture2D m_Q_Letter;
	Texture2D m_AnimOsu;
	Texture2D m_TexTv;
	Texture2D m_TexTelescope;

	Texture2D m_BookDesk;

	Image m_Image;
	Image m_AnimOsuImage;

public:
	Triggers();
	~Triggers();

	void triggerCoords();

	void collisionTrigger(const Vector2& Pos, 
		std::function<void(Vector2)> changePos, 
		Scene::Level currentLevel,
		std::function<void(Scene::Level)> changeLevel, 
		std::function<void(Scene::FadeState)> changeFade);

	void update(const float& deltaTime, Scene::FadeState fadeState);
	void draw(const Vector2& Pos, const Vector2& cameraPos, Scene::Level currentLevel, Scene::FadeState fadeState);
};
