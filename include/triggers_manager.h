#pragma once
#include "core.h"
#include "texture_utils.h"
#include "game_enums.h"

class Triggers {
private:

	enum InteractionObjectsVillage {
		TRIGGER_NOTE,
		TRIGGER_ENTER_EXIT_HOUSE,
		TRIGGER_BOOK,
		TRIGGER_TELESCOPE,
		TRIGGER_NOTE2,
		TRIGGER_NOTE3,
		TRIGGER_NOTE4
	};

	enum InteractionObjectsInsideHouse {
		TRIGGER_TV
	};

	enum InteractionState {
		STATE_INACTIVE,
		STATE_PROMPT,
		STATE_ACTIVE
	};

	enum NoteCycle {
		STATE_ENDING,
		STATE_INTRO,
		STATE_DESCRIPTION,
		STATE_DESCRIPTION2
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

	std::unordered_map<std::string, int> m_LevelMap;

	const float m_TileSize;
	const float m_Scale;
	const std::array<std::array<Rectangle, 30>, 60>& m_GroundMap;

	TriggerInteraction m_TvTrigger;
	TriggerInteraction m_BookTrigger;
	TriggerInteraction m_TelescopeTrigger;
	TriggerInteraction m_NoteTrigger;
	TriggerInteraction m_NoteTrigger2;
	TriggerInteraction m_NoteTrigger3_1;
	TriggerInteraction m_NoteTrigger4_1;

	bool m_EnterHousePrompt;
	bool m_ExitHousePrompt;

	int m_Frames;
	int m_CurrentAnimFrame;
	int m_FrameDelay;
	int m_FrameCounter;
	unsigned int m_NextFrameDataOffset;

	int m_NoteCycleErasmus;
	int m_NoteCycleUniversity;
	int m_OsuCycle;

	Vector2 m_OpacityBoxPosition;
	Vector2 m_OpacityBoxSize;

	std::vector<std::vector<Rectangle>> m_TriggersLevel;

	Texture2D m_Board;
	Texture2D m_Board2;
	Texture2D m_Board3_1;
	Texture2D m_Board3_2;
	Texture2D m_Board3_3;
	Texture2D m_Board4_1;
	Texture2D m_Board4_2;
	Texture2D m_Board4_3;
	Texture2D m_Board4_4;
	Texture2D m_E_Letter;
	Texture2D m_Q_Letter;
	Texture2D m_AnimOsu;
	Texture2D m_TexTv;
	Texture2D m_OsuNote;
	Texture2D m_TexTelescope;

	Texture2D m_BookDesk;
	Image m_AnimOsuImage;

public:

	Triggers(const float& TileSize, const float& Scale, const int& ScreenWidth, const int& ScreenHeight, const std::array<std::array<Rectangle, 30>, 60>& groundMap);
	~Triggers();

	void loadTriggersFromJSON(const std::string& filename);
	void update(const Vector2& Pos,
		std::function<void(Vector2)> changePos, 
		Scene::Level currentLevel,
		std::function<void(Scene::Level)> changeLevel, 
		std::function<void(Scene::FadeState)> changeFade);

	void update(const float& deltaTime, Scene::FadeState fadeState);
	void draw(const Vector2& Pos, const Vector2& cameraPos, Scene::Level currentLevel, Scene::FadeState fadeState);
};