#include "Triggers.h"


Triggers::Triggers() : 
	read(false),
	note(false),
	noteOpened(false) {
	scroll = LoadTexture(RESOURCES_PATH "scroll.png");
}

Triggers::~Triggers() {
	UnloadTexture(scroll);
}

void Triggers::triggerCoords() {
	triggers.emplace_back(Rectangle{ groundMap[34][0].x, groundMap[0][13].y, 3 * (tileSize * scale), 1 * (tileSize * scale) });
}

void Triggers::collisionTrigger(const Vector2& Pos) {
	triggerCoords();
	Rectangle correctCollision = { Pos.x, Pos.y, tileSize * scale, tileSize * scale };
	for (const Rectangle& trigger : triggers) {
		if (CheckCollisionRecs(correctCollision, trigger)) {
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
	}
}

void Triggers::update(const Vector2& Pos) {
	collisionTrigger(Pos);
}


void Triggers::draw(const Vector2& Pos) {

	if (IsKeyDown(KEY_T)) {
		for (Rectangle& trigger : triggers) {
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
}
