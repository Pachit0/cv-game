#include "Triggers.h"

Triggers::Triggers() :
	m_Frames(0),
	m_CurrentAnimFrame(0),
	m_FrameDelay(3),
	m_FrameCounter(0),
	m_NextFrameDataOffset(0),
	m_EnterHousePrompt(false),
	m_ExitHousePrompt(false)
{
	m_Image = LoadImage(RESOURCES_PATH "Map/description of me.png");
	m_Scroll = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "pop-ups/1.png");
	ImageResize(&m_Image, m_Image.width * scale, m_Image.height * scale);
	m_Paper = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "letters/letter_e_press.png");
	m_E_Letter = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "letters/letter_q_press.png");
	m_Q_Letter = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "pop-ups/5-manga+comment.png");
	m_BookDesk = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/tv.png");
	m_TexTv = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_Image = LoadImage(RESOURCES_PATH "Map/telescopeView.png");
	m_TexTelescope = LoadTextureFromImage(m_Image);
	UnloadImage(m_Image);

	m_AnimOsuImage = LoadImageAnim(RESOURCES_PATH "Map/osu.gif", &m_Frames);
	m_AnimOsu = LoadTextureFromImage(m_AnimOsuImage);

	m_TriggersLevel.resize(3);
	m_TriggersLevel[Scene::Level::village].reserve(5);
	m_TriggersLevel[Scene::Level::insideHouse].reserve(3);
}

Triggers::~Triggers() {
	UnloadTexture(m_Scroll);
	UnloadTexture(m_Paper);
	UnloadTexture(m_E_Letter);
	UnloadTexture(m_Q_Letter);
	UnloadTexture(m_BookDesk);
	UnloadTexture(m_AnimOsu);
	UnloadTexture(m_TexTv);
	UnloadImage(m_AnimOsuImage);
}

void Triggers::triggerCoords() {
	m_TriggersLevel[Scene::Level::village].emplace_back(Rectangle{ groundMap[34][0].x, groundMap[0][13].y, 3 * (tileSize * scale), tileSize * scale });
	m_TriggersLevel[Scene::Level::village].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][12].y, tileSize * scale, tileSize * scale });
	m_TriggersLevel[Scene::Level::village].emplace_back(Rectangle{ groundMap[18][0].x, groundMap[0][13].y, 3 * (tileSize * scale), tileSize * scale });
	m_TriggersLevel[Scene::Level::village].emplace_back(Rectangle{ groundMap[38][0].x, groundMap[0][3].y, tileSize * scale, tileSize * scale });
	m_TriggersLevel[Scene::Level::insideHouse].emplace_back(Rectangle{ groundMap[38][0].x - tileSize, groundMap[0][4].y + 12, ((tileSize)*scale), (tileSize)*scale });
	m_TriggersLevel[Scene::Level::insideHouse].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][13].y, tileSize * scale, tileSize * scale });
}

void Triggers::collisionTrigger(const Vector2& Pos, std::function<void(Vector2)> changePos, 
	Scene::Level currentLevel, 
	std::function<void(Scene::Level)> changeLevel, 
	std::function<void(Scene::FadeState)> changeFade)
{

	triggerCoords();
	Rectangle correctCollision = { Pos.x, Pos.y, tileSize * scale, tileSize * scale };

	m_TvTrigger.updateTrigger(correctCollision, m_TriggersLevel[Scene::Level::insideHouse][0]);
	m_NoteTrigger.updateTrigger(correctCollision, m_TriggersLevel[Scene::Level::village][0]);
	m_TelescopeTrigger.updateTrigger(correctCollision, m_TriggersLevel[Scene::Level::village][3]);
	m_BookTrigger.updateTrigger(correctCollision, m_TriggersLevel[Scene::Level::village][2]);

	if (CheckCollisionRecs(correctCollision, m_TriggersLevel[Scene::Level::village][1]) && currentLevel == Scene::Level::village) {
		m_EnterHousePrompt = true;
		if (IsKeyPressed(KEY_E)) {
			changeFade(Scene::FadeState::FADE_IN);
			changeLevel(Scene::Level::insideHouse);
			changePos({ 1440, 570 });
		}
	}
	else if (CheckCollisionRecs(correctCollision, m_TriggersLevel[Scene::Level::insideHouse][1]) && currentLevel == Scene::Level::insideHouse) {
		m_ExitHousePrompt = true;
		if (IsKeyPressed(KEY_E)) {
			changeFade(Scene::FadeState::FADE_IN);
			changeLevel(Scene::Level::village);
			changePos({ 1440, 670 });
		}
	}
	else {
		m_EnterHousePrompt = false;
		m_ExitHousePrompt = false;
	}

}

void Triggers::update(const float& deltaTime, Scene::FadeState fadeState) {
}

void Triggers::draw(const Vector2& Pos, const Vector2& cameraPos, Scene::Level currentLevel, Scene::FadeState fadeState) {

	if (IsKeyDown(KEY_Y)) {
		for (Rectangle& trigger : m_TriggersLevel[currentLevel]) {
			DrawRectangleLines(trigger.x + tileSize * scale, trigger.y + (tileSize * 2) * scale, trigger.width, trigger.height, BLUE);
		}
	}

	if (m_NoteTrigger.isPrompting()) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}
	if (m_NoteTrigger.isActive()) {
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, Fade(BLACK, 0.75));
		DrawTexture(m_Scroll, cameraPos.x - 400, cameraPos.y - 300, WHITE);
		DrawTexture(m_Q_Letter, cameraPos.x - 100, cameraPos.y + 300, WHITE);
	}

	if (m_EnterHousePrompt && fadeState != Scene::FadeState::FADE_IN) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_ExitHousePrompt && fadeState != Scene::FadeState::FADE_IN) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_TvTrigger.isPrompting()) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}


	if (m_TvTrigger.isActive()) {
		m_FrameCounter++;

		if (m_FrameCounter >= m_FrameDelay)
		{
			m_CurrentAnimFrame++;
			if (m_CurrentAnimFrame >= m_Frames) m_CurrentAnimFrame = 0;

			m_NextFrameDataOffset = m_AnimOsu.width * m_AnimOsu.height * 4 * m_CurrentAnimFrame;

			UpdateTexture(m_AnimOsu, ((unsigned char*)m_AnimOsuImage.data) + m_NextFrameDataOffset);

			m_FrameCounter = 0;
		}
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, Fade(BLACK, 0.75));
		DrawTexture(m_TexTv, groundMap[28][0].x, groundMap[0][3].y, WHITE);
		DrawTexture(m_AnimOsu, groundMap[32][0].x - tileSize, groundMap[0][7].y + tileSize, WHITE);
		DrawTexture(m_Q_Letter, groundMap[34][0].x + (tileSize * 2), groundMap[0][14].y, WHITE);
	}

	if (m_BookTrigger.isPrompting()) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_BookTrigger.isActive()) {
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, Fade(BLACK, 0.75));
		DrawTexture(m_BookDesk, Pos.x - 400, Pos.y - 300, WHITE);
		DrawTexture(m_Q_Letter, Pos.x - 75, Pos.y + 300, WHITE);
	}

	if (m_TelescopeTrigger.isPrompting()) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_TelescopeTrigger.isActive()) {
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, BLACK);
		DrawTexture(m_TexTelescope, cameraPos.x - 475, cameraPos.y - 300, WHITE);
		DrawTexture(m_Q_Letter, cameraPos.x - 75, cameraPos.y + 225, WHITE);
	}
}
