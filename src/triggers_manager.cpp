#include "triggers_manager.h"


Triggers::Triggers(const float& TileSize, const float& Scale, const int& ScreenWidth, const int& ScreenHeight, const std::array<std::array<Rectangle, 30>, 60>& groundMap) :
	m_Frames(0),
	m_CurrentAnimFrame(0),
	m_FrameDelay(3),
	m_FrameCounter(0),
	m_NextFrameDataOffset(0),
	m_EnterHousePrompt(false),
	m_ExitHousePrompt(false),
	m_TileSize(TileSize),
	m_Scale(Scale),
	m_OpacityBoxPosition({ 0,0 }),
	m_OpacityBoxSize({ (float)ScreenWidth * 2, (float)ScreenHeight * 2 }),
	m_GroundMap(groundMap)
{
	m_Scroll = LoadFilteredTexture(RESOURCES_PATH "Map/description of me.png");
	m_E_Letter = LoadFilteredTexture(RESOURCES_PATH "letters/letter_e_press.png");
	m_Q_Letter = LoadFilteredTexture(RESOURCES_PATH "letters/letter_q_press.png");
	m_BookDesk = LoadFilteredTexture(RESOURCES_PATH "pop-ups/5-manga+comment.png");
	m_TexTv = LoadFilteredTexture(RESOURCES_PATH "Map/tv.png");
	m_TexTelescope = LoadFilteredTexture(RESOURCES_PATH "Map/telescopeView.png");

	m_AnimOsuImage = LoadImageAnim(RESOURCES_PATH "Map/osu.gif", &m_Frames);
	m_AnimOsu = LoadTextureFromImage(m_AnimOsuImage);

	m_TriggersLevel.resize(3);
	m_TriggersLevel[Scene::Level::village].reserve(5);
	m_TriggersLevel[Scene::Level::insideHouse].reserve(3);
}

Triggers::~Triggers() {
	UnloadTexture(m_Scroll);
	UnloadTexture(m_E_Letter);
	UnloadTexture(m_Q_Letter);
	UnloadTexture(m_BookDesk);
	UnloadTexture(m_AnimOsu);
	UnloadTexture(m_TexTv);
	UnloadImage(m_AnimOsuImage);
}

void Triggers::loadTriggersFromJSON(const std::string& filename) {
	nlohmann::json Data;
	std::ifstream File;

	int levelIndex;
	float x;
	float y;
	float width;
	float height;

	File.open(filename);
	if (!File.is_open()) {
		std::cerr << "file couldn't open" << std::endl;
		return;
	}

	File >> Data;

	m_LevelMap = {
		{"village", Scene::Level::village},
		{"insideHouse", Scene::Level::insideHouse}
	};

	for (const auto& [levelName, items] : Data.items()) {
		auto it = m_LevelMap.find(levelName);
		if (it == m_LevelMap.end()) continue;
		levelIndex = it->second;

		for (const auto& item : items) {
			x = m_GroundMap[item["tileX"]][0].x;
			y = m_GroundMap[0][item["tileY"]].y;

			if (item.contains("offsetX")) x += item["offsetX"];
			if (item.contains("offsetY")) y += item["offsetY"];

			width = item["widthInTiles"] * (m_TileSize * m_Scale);
			height = item["heightInTiles"] * (m_TileSize * m_Scale);

			m_TriggersLevel[levelIndex].emplace_back(Rectangle{ x,y,width,height });
		}
	}

	File.close();

}

void Triggers::update(const Vector2& Pos, std::function<void(Vector2)> changePos,
	Scene::Level currentLevel, 
	std::function<void(Scene::Level)> changeLevel, 
	std::function<void(Scene::FadeState)> changeFade)
{

	Rectangle correctCollision = { Pos.x, Pos.y, m_TileSize * m_Scale, m_TileSize * m_Scale };

	switch (currentLevel) {
	case Scene::Level::village: {
		m_NoteTrigger.updateTrigger(correctCollision, m_TriggersLevel[Scene::Level::village][TRIGGER_NOTE]);
		m_TelescopeTrigger.updateTrigger(correctCollision, m_TriggersLevel[Scene::Level::village][TRIGGER_TELESCOPE]);
		m_BookTrigger.updateTrigger(correctCollision, m_TriggersLevel[Scene::Level::village][TRIGGER_BOOK]);
		break;
	}
	case Scene::Level::insideHouse: {
		m_TvTrigger.updateTrigger(correctCollision, m_TriggersLevel[Scene::Level::insideHouse][TRIGGER_TV]);
		break;
		}
	default:
		break;
	}

	if (CheckCollisionRecs(correctCollision, m_TriggersLevel[Scene::Level::village][TRIGGER_ENTER_EXIT_HOUSE]) && currentLevel == Scene::Level::village) {
		m_EnterHousePrompt = true;
		if (IsKeyPressed(KEY_E)) {
			changeFade(Scene::FadeState::FADE_IN);
			changeLevel(Scene::Level::insideHouse);
			changePos({ 1440, 570 });
		}
	}
	else if (CheckCollisionRecs(correctCollision, m_TriggersLevel[Scene::Level::insideHouse][TRIGGER_ENTER_EXIT_HOUSE]) && currentLevel == Scene::Level::insideHouse) {
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

void Triggers::draw(const Vector2& Pos, const Vector2& cameraPos, Scene::Level currentLevel, Scene::FadeState fadeState) {

	if (IsKeyDown(KEY_Y)) {
		for (Rectangle& trigger : m_TriggersLevel[currentLevel]) {
			DrawRectangleLines(trigger.x + m_TileSize * m_Scale, trigger.y + (m_TileSize * 2) * m_Scale, trigger.width, trigger.height, BLUE);
		}
	}

	if (m_NoteTrigger.isPrompting()) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}
	if (m_NoteTrigger.isActive()) {
		DrawRectangleV(m_OpacityBoxPosition, m_OpacityBoxSize, Fade(BLACK, 0.75));
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
		DrawRectangleV(m_OpacityBoxPosition, m_OpacityBoxSize, Fade(BLACK, 0.75));
		DrawTexture(m_TexTv, m_GroundMap[28][0].x, m_GroundMap[0][3].y, WHITE);
		DrawTexture(m_AnimOsu, m_GroundMap[32][0].x - m_TileSize, m_GroundMap[0][7].y + m_TileSize, WHITE);
		DrawTexture(m_Q_Letter, m_GroundMap[34][0].x + (m_TileSize * 2), m_GroundMap[0][14].y, WHITE);
	}

	if (m_BookTrigger.isPrompting()) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_BookTrigger.isActive()) {
		DrawRectangleV(m_OpacityBoxPosition, m_OpacityBoxSize, Fade(BLACK, 0.75));
		DrawTexture(m_BookDesk, Pos.x - 400, Pos.y - 300, WHITE);
		DrawTexture(m_Q_Letter, Pos.x - 75, Pos.y + 300, WHITE);
	}

	if (m_TelescopeTrigger.isPrompting()) {
		DrawTexture(m_E_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (m_TelescopeTrigger.isActive()) {
		DrawRectangleV(m_OpacityBoxPosition, m_OpacityBoxSize, BLACK);
		DrawTexture(m_TexTelescope, cameraPos.x - 475, cameraPos.y - 300, WHITE);
		DrawTexture(m_Q_Letter, cameraPos.x - 75, cameraPos.y + 225, WHITE);
	}
}
