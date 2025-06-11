#include "Triggers.h"


Triggers::Triggers() :
	read(false),
	note(false),
	noteOpened(false),
	enterHouse(false),
	tv(false),
	tvOpened(false),
	tvWatching(false),
	exitHouse(false)
	{
	scroll = LoadTexture(RESOURCES_PATH "scroll.png");

	image = LoadImage(RESOURCES_PATH "Humble Gift - Paper UI System v1.1/Sprites/Paper UI Pack/Folding & Cutout/5 Mini Map/1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	paper = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "letter_e_press.png");
	e_Letter = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "letter_q_press.png");
	q_Letter = LoadTextureFromImage(image);
	UnloadImage(image);

	triggersLevel.resize(3);
	triggersLevel[village].reserve(5);
	triggersLevel[insideHouse].reserve(3);

}

Triggers::~Triggers() {
	UnloadTexture(scroll);
	UnloadTexture(paper);
	UnloadTexture(e_Letter);
}

void Triggers::triggerCoords() {
	triggersLevel[village].emplace_back(Rectangle{groundMap[34][0].x, groundMap[0][13].y, 3 * (tileSize * scale), tileSize * scale});
	triggersLevel[village].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][12].y, tileSize * scale, tileSize * scale });
	triggersLevel[insideHouse].emplace_back(Rectangle{ groundMap[38][0].x - tileSize, groundMap[0][4].y + 12, ((tileSize)*scale), (tileSize)*scale });
	triggersLevel[insideHouse].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][13].y, tileSize*scale, tileSize*scale });
}
void Triggers::collisionTrigger(const Vector2& Pos, std::function<void(Vector2)> changePos) {
	triggerCoords();
	Rectangle correctCollision = { Pos.x, Pos.y, tileSize * scale, tileSize * scale };
	if (CheckCollisionRecs(correctCollision, triggersLevel[village][0]) && currentLevel == village) {
		if (!noteOpened) {
			read = true;
		}
		if (IsKeyPressed(KEY_E)) {
			note = true;
			read = false;
			noteOpened = true;
		}
		else if (IsKeyPressed(KEY_Q)) {
			note = false;
			noteOpened = false;
		}
	}
	else {
		read = false;
		note = false;
		noteOpened = false;
	}

	if (CheckCollisionRecs(correctCollision, triggersLevel[village][1]) && currentLevel == village) {
		enterHouse = true;
		if (IsKeyPressed(KEY_E)) {
			fadeState = FADE_IN;
			fadeAlpha = 0.0f;
			fadeTimer = 0.0f;
			currentLevel = insideHouse;
			changePos({ 1440, 570 });
		}	
	}
	else if (CheckCollisionRecs(correctCollision, triggersLevel[insideHouse][1]) && currentLevel == insideHouse) {
		exitHouse = true;
		if (IsKeyPressed(KEY_E)) {
			fadeState = FADE_IN;
			fadeAlpha = 0.0f;
			fadeTimer = 0.0f;
			currentLevel = village;
			changePos({ 1440, 670 });
		}
	}
	else {
		enterHouse = false;
		exitHouse = false;
	}

	if (CheckCollisionRecs(correctCollision, triggersLevel[insideHouse][0]) && currentLevel == insideHouse) {

		if (!tvOpened) {
			tvWatching = true;
		}
		if (IsKeyPressed(KEY_E)) {
			tv = true;
			tvWatching = false;
			tvOpened = true;
		}
		else if (IsKeyPressed(KEY_Q)) {
			tv = false;
			tvOpened = false;
		}
	}
	else {
		tv = false;
		tvOpened = false;
		tvWatching = false;
	}

}

void Triggers::fadeInControl(const Vector2& Pos) {}

void Triggers::update(const float& deltaTime) {

	switch (fadeState) {
	case FADE_IN:
		fadeAlpha += fadeSpeed * deltaTime;
		if (fadeAlpha >= 1.0f) {
			fadeAlpha = 1.0f;
			fadeState = FADE_HOLD;
			fadeTimer = 0.0f;
		}
		break;

	case FADE_HOLD:
		fadeTimer += deltaTime;
		if (fadeTimer >= fadeHoldTime) {
			fadeState = FADE_OUT;
		}
		break;

	case FADE_OUT:
		fadeAlpha -= fadeSpeed * deltaTime;
		if (fadeAlpha <= 0.0f) {
			fadeAlpha = 0.0f;
			fadeState = FADE_NONE;
		}
		break;

	default:
		break;
	}
}


void Triggers::draw(const Vector2& Pos, const Vector2& cameraPos) {

	if (fadeState != FADE_NONE) {
		DrawRectangle(0, 0, GetScreenWidth() * 3, GetScreenHeight() * 2, Fade(BLACK, fadeAlpha));
	}

	if (IsKeyDown(KEY_Y)) {
		for (Rectangle& trigger : triggersLevel[currentLevel]) {
			DrawRectangleLines(trigger.x + tileSize * scale, trigger.y + (tileSize * 2) * scale, trigger.width, trigger.height, BLUE);
		}
	}

	if (read) {
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}
	if (note) {
		DrawTexture(scroll, 1545, 300, WHITE);
		DrawTexture(q_Letter, Pos.x + 5, Pos.y - 5, WHITE);
		DrawText("You are cute :3", 1620, 400, 30, BLACK);
	}

	if (enterHouse && fadeState != FADE_IN) {
		//DrawText("Press E to enter", 1340, 675, 50, BLACK);
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (tvWatching) {
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (tv) {
		DrawTexture(paper, 1400, 0, WHITE); //placeholder
	}

	if (exitHouse && fadeState != FADE_IN) {
		//DrawText("Press E to exit", 1410, 520, 50, BLACK);
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}
}