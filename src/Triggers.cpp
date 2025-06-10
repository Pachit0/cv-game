#include "Triggers.h"


Triggers::Triggers() : 
	read(false),
	note(false),
	noteOpened(false),
	enterHouse(false),
	tv(false),
	tvOpened(false),
	tvWatching(false),
	exitHouse(false) {
	scroll = LoadTexture(RESOURCES_PATH "scroll.png");


	image = LoadImage(RESOURCES_PATH "Humble Gift - Paper UI System v1.1/Sprites/Paper UI Pack/Folding & Cutout/5 Mini Map/1.png");
	ImageResize(&image, image.width * scale, image.height * scale);
	paper = LoadTextureFromImage(image);
	UnloadImage(image);

	triggersLevel.resize(3);
	triggersLevel[village].reserve(5);
	triggersLevel[insideHouse].reserve(3);

}

Triggers::~Triggers() {
	UnloadTexture(scroll);
	UnloadTexture(paper);
}

void Triggers::triggerCoords() {
	triggersLevel[village].emplace_back(Rectangle{groundMap[34][0].x, groundMap[0][13].y, 3 * (tileSize * scale), tileSize * scale});
	triggersLevel[village].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][13].y, tileSize * scale, tileSize * scale });
	triggersLevel[insideHouse].emplace_back(Rectangle{ groundMap[38][0].x - tileSize, groundMap[0][4].y + 12, ((tileSize)*scale), (tileSize)*scale });
	triggersLevel[insideHouse].emplace_back(Rectangle{ groundMap[30][0].x, groundMap[0][13].y, tileSize*scale, tileSize*scale });
}
void Triggers::collisionTrigger(const Vector2& Pos) {
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
			currentLevel = insideHouse;
		}
	} else {
		enterHouse = false;
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

	if (CheckCollisionRecs(correctCollision, triggersLevel[insideHouse][1]) && currentLevel == insideHouse) {
		exitHouse = true;
		if (IsKeyPressed(KEY_P)) {
			currentLevel = village;
		}
	}
	else {
		exitHouse = false;
	}
}

void Triggers::update(const Vector2& Pos) {
	collisionTrigger(Pos);
}


void Triggers::draw(const Vector2& Pos) {

	if (IsKeyDown(KEY_Y)) {
		for (Rectangle& trigger : triggersLevel[currentLevel]) {
			DrawRectangleLines(trigger.x + tileSize * scale, trigger.y + (tileSize * 2) * scale, trigger.width, trigger.height, BLUE);
		}
	}

	if (read) {
		DrawText("Press E", Pos.x - 20, Pos.y - 25, 50, BLACK);
	}
	if (note) {
		DrawTexture(scroll, 1545, 300, WHITE);
		DrawText("Press Q to exit", 1550, 500, 50, BLACK);
		DrawText("You are cute :3", 1620, 400, 30, BLACK);
	}

	if (enterHouse) {
		DrawText("Press E to enter", Pos.x - 100, Pos.y - 25, 50, BLACK);
	}


	if (tvWatching) {
		DrawText("Press E", Pos.x - 20, Pos.y - 25, 50, BLACK);
	}

	if (tv) {
		DrawTexture(paper, 1400, 0, WHITE); //placeholder
	}

	if (exitHouse) {
		DrawText("Press P to exit", Pos.x - 100, Pos.y - 25, 50, BLACK);
	}
}
