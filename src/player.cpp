#include "player.h"

Player::Player() :
	speed(200.0f),
	directions(DOWN),
	frameIndex(0),
	frameDelay(10),
	frameDelayCount(0),
	frameNum(7),
	Pos({1440,670 }),
	velocity({0,0})

{
	image = LoadImage(RESOURCES_PATH "TheAdventurer/Idle/idle.png");

	ImageResize(&image, 384 * 3, 384 * 3);
	idle = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage(RESOURCES_PATH "TheAdventurer/Walk/walk.png");
	ImageResize(&image, 384 * 3, 384 * 3);

	walk = LoadTextureFromImage(image);
	UnloadImage(image);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			movement_Rect[i][j] = { j * 48.0f * scale, i * 64.0f * scale, 48.0f * scale, 64.0f * scale };
		}
	}
}

Player::~Player() {
	UnloadTexture(idle);
	UnloadTexture(walk);
}

void Player::inputHandling() {

	velocity = { 0,0 };

	if (IsKeyDown(KEY_A)) {
		velocity.x = -speed;
	}
	else if (IsKeyDown(KEY_D)) {
		velocity.x = speed;
	}

	if (IsKeyDown(KEY_S)) {
		velocity.y = speed;
	}
	if (IsKeyDown(KEY_W)) {
		velocity.y = -speed;
	}

	// Diagonal movement correction
	if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W)) {
		velocity.y = -speed + 30;
	}
	if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) {
		velocity.y = speed - 30;
	}
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W)) {
		velocity.y = -speed + 30;
	}
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_S)) {
		velocity.y = speed - 30;
	}
}

void Player::handleCurrentDirection() {
	if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) {
		directions = LEFT_UP;
	}
	else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) {
		directions = RIGHT_UP;
	}
	else if (IsKeyDown(KEY_A)) {
		directions = LEFT_DOWN;
	}
	else if (IsKeyDown(KEY_D)) {
		directions = RIGHT_DOWN;
	}
	else if (IsKeyDown(KEY_W)) {
		directions = UP;
	}
	else if (IsKeyDown(KEY_S)) {
		directions = DOWN;
	}
}

void Player::Update(const float& deltaTime) {

	Pos.x += velocity.x * deltaTime;
	Pos.y += velocity.y * deltaTime;

	if (IsKeyPressed(KEY_B)) {
		std::cout << "Pos x: " << Pos.x << "  " << "Pos y: " << Pos.y << std::endl;
	}

}

void Player::Draw() {
	++frameDelayCount;
	if (frameDelayCount > frameDelay) {
		frameDelayCount = 0;
		++frameIndex;
		frameIndex %= frameNum;
	}

	if (!velocity.x && !velocity.y) {
		if (IsKeyDown(KEY_T) && frameIndex <= 5) {
			DrawTextureRec(idle, movement_Rect[frameIndex][0], Pos, WHITE);
		}
		else {
			switch (directions) {
			case DOWN: {
				DrawTextureRec(idle, movement_Rect[DOWN][frameIndex], Pos, WHITE);
				break;
			}
			case UP: {
				DrawTextureRec(idle, movement_Rect[UP][frameIndex], Pos, WHITE);
				break;
			}
			case LEFT_DOWN: {
				DrawTextureRec(idle, movement_Rect[LEFT_DOWN][frameIndex], Pos, WHITE);
				break;
			}
			case LEFT_UP: {
				DrawTextureRec(idle, movement_Rect[LEFT_UP][frameIndex], Pos, WHITE);
				break;
			}
			case RIGHT_UP: {
				DrawTextureRec(idle, movement_Rect[RIGHT_UP][frameIndex], Pos, WHITE);
				break;
			}
			case RIGHT_DOWN: {
				DrawTextureRec(idle, movement_Rect[RIGHT_DOWN][frameIndex], Pos, WHITE);
				break;
			}
			}
		}

	}
	else {
		switch (directions) {
		case DOWN: {
			DrawTextureRec(walk, movement_Rect[DOWN][frameIndex], Pos, WHITE);
			break;
		}
		case UP: {
			DrawTextureRec(walk, movement_Rect[UP][frameIndex], Pos, WHITE);
			break;
		}
		case LEFT_DOWN: {
			DrawTextureRec(walk, movement_Rect[LEFT_DOWN][frameIndex], Pos, WHITE);
			break;
		}
		case LEFT_UP: {
			DrawTextureRec(walk, movement_Rect[LEFT_UP][frameIndex], Pos, WHITE);
			break;
		}
		case RIGHT_UP: {
			DrawTextureRec(walk, movement_Rect[RIGHT_UP][frameIndex], Pos, WHITE);
			break;
		}
		case RIGHT_DOWN: {
			DrawTextureRec(walk, movement_Rect[RIGHT_DOWN][frameIndex], Pos, WHITE);
			break;
			}
		}
	}
}
