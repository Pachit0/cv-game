#include "Triggers.h"

Triggers::Triggers() :
	read(false),
	note(false),
	noteOpened(false),
	enterHouse(false),
	tv(false),
	tvOpened(false),
	tvWatching(false),
	exitHouse(false),
	bookOpened(false),
	bookWatching(false),
	book(false),
	telescopeOpened(false),
	telescopeWatching(false),
	telescope(false),
	frames(0),
	currentAnimFrame(0),
	frameDelay(3),
	frameCounter(0),
	nextFrameDataOffset(0)
	{
	image = LoadImage(RESOURCES_PATH "Map/description of me.png");
	scroll = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "pop-ups/1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	paper = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "letters/letter_e_press.png");
	e_Letter = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "letters/letter_q_press.png");
	q_Letter = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "pop-ups/5-manga+comment.png");
	bookDesk = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/tv.png");
	texTv = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "Map/telescopeView.png");
	texTelescope = LoadTextureFromImage(image);
	UnloadImage(image);

	animOsuImage = LoadImageAnim(RESOURCES_PATH "Map/osu.gif", &frames);
	animOsu = LoadTextureFromImage(animOsuImage);

	triggersLevel.resize(3);
	triggersLevel[village].reserve(5);
	triggersLevel[insideHouse].reserve(3);

}

Triggers::~Triggers() {
	UnloadTexture(scroll);
	UnloadTexture(paper);
	UnloadTexture(e_Letter);
	UnloadTexture(q_Letter);
	UnloadTexture(bookDesk);
	UnloadTexture(animOsu);
	UnloadTexture(texTv);
	UnloadImage(animOsuImage);
}

void Triggers::triggerCoords() {
	triggersLevel[village].emplace_back(Rectangle{groundMap[34][0].x, groundMap[0][13].y, 3 * (tileSize * scale), tileSize * scale});
	triggersLevel[village].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][12].y, tileSize * scale, tileSize * scale });
	triggersLevel[village].emplace_back(Rectangle{ groundMap[18][0].x, groundMap[0][13].y, 3 * (tileSize * scale), tileSize * scale });
	triggersLevel[village].emplace_back(Rectangle{ groundMap[38][0].x, groundMap[0][3].y, tileSize * scale, tileSize * scale });
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

	if (CheckCollisionRecs(correctCollision, triggersLevel[village][3]) && currentLevel == village) {

		if (!tvOpened) {
			telescopeWatching = true;
		}
		if (IsKeyPressed(KEY_E)) {
			telescope = true;
			telescopeWatching = false;
			telescopeOpened = true;
		}
		else if (IsKeyPressed(KEY_Q)) {
			telescope = false;
			telescopeOpened = false;
		}
	}
	else {
		telescope = false;
		telescopeOpened = false;
		telescopeWatching = false;
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
	if (CheckCollisionRecs(correctCollision, triggersLevel[village][2]) && currentLevel == village) {

		if (!tvOpened) {
			bookWatching = true;
		}
		if (IsKeyPressed(KEY_E)) {
			book = true;
			bookWatching = false;
			bookOpened = true;
		}
		else if (IsKeyPressed(KEY_Q)) {
			book = false;
			bookOpened = false;
		}
	}
	else {
		book = false;
		bookOpened = false;
		bookWatching = false;
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
		for (Rectangle& trigger : triggersLevel[currentLevel]) {
			DrawRectangleLines(trigger.x + tileSize * scale, trigger.y + (tileSize * 2) * scale, trigger.width, trigger.height, BLUE);
		}
	}

	if (read) {
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}
	if (note) {
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, Fade(BLACK, 0.75));
		DrawTexture(scroll, cameraPos.x - 400, cameraPos.y - 300, WHITE);
		DrawTexture(q_Letter, cameraPos.x - 100, cameraPos.y + 300, WHITE);
	}

	if (enterHouse && fadeState != FADE_IN) {
		//DrawText("Press E to enter", 1340, 675, 50, BLACK);
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (tvWatching) {
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (tv) {
		frameCounter++;

		if (frameCounter >= frameDelay)
		{

			currentAnimFrame++;
			if (currentAnimFrame >= frames) currentAnimFrame = 0;

			nextFrameDataOffset = animOsu.width * animOsu.height * 4 * currentAnimFrame;

			UpdateTexture(animOsu, ((unsigned char*)animOsuImage.data) + nextFrameDataOffset);

			frameCounter = 0;
		}
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, Fade(BLACK, 0.75));
		DrawTexture(texTv, groundMap[28][0].x, groundMap[0][3].y, WHITE);
		DrawTexture(animOsu, groundMap[32][0].x - tileSize, groundMap[0][7].y + tileSize, WHITE);
		DrawTexture(q_Letter, groundMap[34][0].x + (tileSize * 2), groundMap[0][14].y, WHITE);
	}

	if (exitHouse && fadeState != FADE_IN) {
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (bookWatching) {
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (book) {
		DrawRectangle(0,0, screenWidth * 2, screenHeight * 2, Fade(BLACK, 0.75));
		DrawTexture(bookDesk, Pos.x - 400, Pos.y - 300, WHITE);
		DrawTexture(q_Letter, Pos.x - 75, Pos.y + 300, WHITE);
	}

	if (telescopeWatching) {
		DrawTexture(e_Letter, Pos.x + 5, Pos.y - 5, WHITE);
	}

	if (telescope) {
		DrawRectangle(0, 0, screenWidth * 2, screenHeight * 2, BLACK);
		DrawTexture(texTelescope, cameraPos.x - 475, cameraPos.y - 300, WHITE);
		DrawTexture(q_Letter, cameraPos.x - 75, cameraPos.y + 225, WHITE);
	}
}