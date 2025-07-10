#include "Triggers.h"

Triggers::Triggers() :
	m_Read(false),
	m_Note(false),
	m_NoteOpened(false),
	m_EnterHouse(false),
	m_Tv(false),
	m_TvOpened(false),
	m_TvWatching(false),
	m_ExitHouse(false),
	m_BookOpened(false),
	m_BookWatching(false),
	m_Book(false),
	m_TelescopeOpened(false),
	m_TelescopeWatching(false),
	m_Telescope(false),
	m_Frames(0),
	m_CurrentAnimFrame(0),
	m_FrameDelay(3),
	m_FrameCounter(0),
	m_NextFrameDataOffset(0)
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
	m_TriggersLevel[village].reserve(5);
	m_TriggersLevel[insideHouse].reserve(3);
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
	m_TriggersLevel[village].emplace_back(Rectangle{ groundMap[34][0].x, groundMap[0][13].y, 3 * (tileSize * scale), tileSize * scale });
	m_TriggersLevel[village].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][12].y, tileSize * scale, tileSize * scale });
	m_TriggersLevel[village].emplace_back(Rectangle{ groundMap[18][0].x, groundMap[0][13].y, 3 * (tileSize * scale), tileSize * scale });
	m_TriggersLevel[village].emplace_back(Rectangle{ groundMap[38][0].x, groundMap[0][3].y, tileSize * scale, tileSize * scale });
	m_TriggersLevel[insideHouse].emplace_back(Rectangle{ groundMap[38][0].x - tileSize, groundMap[0][4].y + 12, ((tileSize)*scale), (tileSize)*scale });
	m_TriggersLevel[insideHouse].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][13].y, tileSize * scale, tileSize * scale });
}

void Triggers::collisionTrigger(const Vector2& Pos, std::function<void(Vector2)> changePos) {
	triggerCoords();
	Rectangle correctCollision = { Pos.x, Pos.y, tileSize * scale, tileSize * scale };
	if (CheckCollisionRecs(correctCollision, m_TriggersLevel[village][0]) && currentLevel == village) {
		if (!m_NoteOpened) {
			m_Read = true;
		}
		if (IsKeyPressed(KEY_E)) {
			m_Note = true;
			m_Read = false;
			m_NoteOpened = true;
		}
		else if (IsKeyPressed(KEY_Q)) {
			m_Note = false;
			m_NoteOpened = false;
		}
	}
	else {
		m_Read = false;
		m_Note = false;
		m_NoteOpened = false;
	}

	if (CheckCollisionRecs(correctCollision, m_TriggersLevel[village][3]) && currentLevel == village) {

		if (!m_TvOpened) {
			m_TelescopeWatching = true;
		}
		if (IsKeyPressed(KEY_E)) {
			m_Telescope = true;
			m_TelescopeWatching = false;
			m_TelescopeOpened = true;
		}
		else if (IsKeyPressed(KEY_Q)) {
			m_Telescope = false;
			m_TelescopeOpened = false;
		}
	}
	else {
		m_Telescope = false;
		m_TelescopeOpened = false;
		m_TelescopeWatching = false;
	}

	if (CheckCollisionRecs(correctCollision, m_TriggersLevel[village][1]) && currentLevel == village) {
		m_EnterHouse = true;
		if (IsKeyPressed(KEY_E)) {
			fadeState = FADE_IN;
			fadeAlpha = 0.0f;
			fadeTimer = 0.0f;
			currentLevel = insideHouse;
			changePos({ 1440, 570 });
		}
	}
	else if (CheckCollisionRecs(correctCollision, m_TriggersLevel[insideHouse][1]) && currentLevel == insideHouse) {
		m_ExitHouse = true;
		if (IsKeyPressed(KEY_E)) {
			fadeState = FADE_IN;
			fadeAlpha = 0.0f;
			fadeTimer = 0.0f;
			currentLevel = village;
			changePos({ 1440, 670 });
		}
	}
	else {
		m_EnterHouse = false;
		m_ExitHouse = false;
	}
	if (CheckCollisionRecs(correctCollision, m_TriggersLevel[village][2]) && currentLevel == village) {

		if (!m_TvOpened) {
			m_BookWatching = true;
		}
		if (IsKeyPressed(KEY_E)) {
			m_Book = true;
			m_BookWatching = false;
			m_BookOpened = true;
		}
		else if (IsKeyPressed(KEY_Q)) {
			m_Book = false;
			m_BookOpened = false;
		}
	}
	else {
		m_Book = false;
		m_BookOpened = false;
		m_BookWatching = false;
	}

	if (CheckCollisionRecs(correctCollision, m_TriggersLevel[insideHouse][0]) && currentLevel == insideHouse) {

		if (!m_TvOpened) {
			m_TvWatching = true;
		}
		if (IsKeyPressed(KEY_E)) {
			m_Tv = true;
			m_TvWatching = false;
			m_TvOpened = true;
		}
		else if (IsKeyPressed(KEY_Q)) {
			m_Tv = false;
			m_TvOpened = false;
		}
	}
	else {
		m_Tv = false;
		m_TvOpened = false;
		m_TvWatching = false;
	}

}

void Triggers::update(const float& deltaTime) {

	switch (fadeState) {
	case FADE_IN: {
		fadeAlpha += fadeSpeed * deltaTime;
		if (fadeAlpha >= 1.0f) {
			fadeAlpha = 1.0f;
			fadeState = FADE_HOLD;
			fadeTimer = 0.0f;
		}
		break;
	}

	case FADE_HOLD: {
		fadeTimer += deltaTime;
		if (fadeTimer >= fadeHoldTime) {
			fadeState = FADE_OUT;
		}
		break;
	}

	case FADE_OUT: {
		fadeAlpha -= fadeSpeed * deltaTime;
		if (fadeAlpha <= 0.0f) {
			fadeAlpha = 0.0f;
			fadeState = FADE_NONE;
		}
		break;
	}

	default:
		break;
	}
}

void Triggers::draw(const Vector2& Pos, const Vector2& cameraPos) {

	if (fadeState != FADE_NONE) {
		DrawRectangle(0, 0, GetScreenWidth() * 3, GetScreenHeight() * 2, Fade(BLACK, fadeAlpha));
	}

	if (IsKeyDown(KEY_Y)) {
		for (Rectangle& trigger : m_TriggersLevel[currentLevel]) {
			DrawRectangleLines(trigger.x + tileSize * scale, trigger.y + (tileSize * 2) * scale, trigger.width, trigger.height, BLUE);
		}
	}

	if (m_Read) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}
	if (m_Note) {
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, Fade(BLACK, 0.75));
		DrawTexture(m_Scroll, cameraPos.x - 400, cameraPos.y - 300, WHITE);
		DrawTexture(m_Q_Letter, cameraPos.x - 100, cameraPos.y + 300, WHITE);
	}

	if (m_EnterHouse && fadeState != FADE_IN) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_TvWatching) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_Tv) {
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

	if (m_ExitHouse && fadeState != FADE_IN) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_BookWatching) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_Book) {
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, Fade(BLACK, 0.75));
		DrawTexture(m_BookDesk, Pos.x - 400, Pos.y - 300, WHITE);
		DrawTexture(m_Q_Letter, Pos.x - 75, Pos.y + 300, WHITE);
	}

	if (m_TelescopeWatching) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_Telescope) {
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, BLACK);
		DrawTexture(m_TexTelescope, cameraPos.x - 475, cameraPos.y - 300, WHITE);
		DrawTexture(m_Q_Letter, cameraPos.x - 75, cameraPos.y + 225, WHITE);
	}
}
