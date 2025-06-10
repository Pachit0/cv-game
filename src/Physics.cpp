#include "physics.h"

Physics::Physics() {
	obstaclesLevel.resize(3);
	obstaclesLevel[village].reserve(50);
	obstaclesLevel[insideHouse].reserve(10);
}

Physics::~Physics() {}

void Physics::objectCoords() {

	//edge of scene
	obstaclesLevel[village].emplace_back(Rectangle{groundMap[1][0].x, groundMap[0][0].y, tileSize * scale, 30 * (tileSize * scale)});
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[59][0].x, groundMap[0][3].y, tileSize * scale, 30 * (tileSize * scale) });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[0][0].x, groundMap[0][2].y, 60 * (tileSize * scale), tileSize * scale });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[0][0].x, groundMap[0][28].y, 60 * (tileSize * scale), tileSize * scale });
	//Fences
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[0][0].x, groundMap[0][17].y, 10 * (tileSize * scale), tileSize * scale });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[9][0].x, groundMap[0][18].y, (tileSize * scale), tileSize * scale });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[10][0].x, groundMap[0][19].y, 42 * (tileSize * scale), tileSize * scale });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[52][0].x, groundMap[0][18].y, (tileSize * scale), tileSize * scale });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[52][0].x, groundMap[0][17].y, 10 * (tileSize * scale), tileSize * scale });

	//house
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[28][0].x + 16, groundMap[0][9].y, 5 * ((tileSize - 2) * scale), 4 * ((tileSize - 2) * scale) });
	//river stuff
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[27][0].x + 16, groundMap[0][3].y - 16, 2 * ((tileSize - 4) * scale), ((tileSize - 2) * scale) });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[30][0].x + 16, groundMap[0][3].y - 16, ((tileSize - 4) * scale), ((tileSize - 2) * scale) });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[25][0].x + 6, groundMap[0][4].y + 16, ((tileSize - 4) * scale), ((tileSize - 4) * scale) });
	//Sign
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[34][0].x, groundMap[0][11].y + tileSize, 3 * ((tileSize) * scale), (tileSize)* scale });
	//Bench
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[39][0].x, groundMap[0][10].y, ((tileSize)*scale), 2 * ((tileSize)*scale) });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[44][0].x + 12, groundMap[0][10].y, ((tileSize - 4)*scale), 2 * ((tileSize)*scale) });
	//Fire Place
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[41][0].x + 4, groundMap[0][11].y, 2 * ((tileSize - 2)*scale), ((tileSize)*scale) });
	//Polls
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[26][0].x + 12, groundMap[0][16].y + 10, (tileSize - 10) * scale, (tileSize - 10) * scale });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[35][0].x + 6, groundMap[0][16].y + 10, (tileSize - 10) * scale, (tileSize - 10) * scale });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[13][0].x + 12, groundMap[0][11].y + 10, (tileSize - 6) * scale, (tileSize - 6) * scale });
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[47][0].x + tileSize, groundMap[0][14].y + tileSize, (tileSize - 8) * scale, (tileSize - 10) * scale });
	//tree right side
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[46][0].x + 28, groundMap[0][12].y , 2 * (tileSize - 4) * scale, (tileSize - 4) * scale });
	//hae & rock
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[23][0].x + tileSize - 6, groundMap[0][12].y, 4 * ((tileSize - 2) * scale), 2 * (tileSize * scale) });
	//table & benches
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[17][0].x + 12 , groundMap[0][11].y, 5 * ((tileSize - 1) * scale), 2 * (tileSize * scale) });
	//Tree Near House
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[24][0].x, groundMap[0][11].y, 2 * (tileSize * scale),  tileSize * scale });
	//cut tree
	obstaclesLevel[village].emplace_back(Rectangle{ groundMap[38][0].x + 12, groundMap[0][14].y, 2 * ((tileSize - 4)*scale), (tileSize)*scale });
	

	//insideHouse - edge
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[28][0].x, groundMap[0][14].y - 12, 13 * ((tileSize)*scale), (tileSize)*scale });
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[28][0].x, groundMap[0][3].y, ((tileSize)*scale), 11 * (tileSize)*scale });
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[28][0].x, groundMap[0][3].y + 12, 13 * ((tileSize)*scale), (tileSize)*scale });
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[40][0].x, groundMap[0][3].y + 12, ((tileSize)*scale), 12 *(tileSize)*scale });

	//walls
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[29][0].x, groundMap[0][7].y, tileSize * 2, 4 * (tileSize * 2)});
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[32][0].x - tileSize, groundMap[0][7].y, 6 * (tileSize * 2), 3 * ((tileSize - 2) * 2)});
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[38][0].x - tileSize, groundMap[0][7].y, 4 * (tileSize * 2), 3 * ((tileSize - 2) * 2)});
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[34][0].x + tileSize, groundMap[0][4].y, (tileSize * scale), 3 * ((tileSize) * scale)});
	
	//chair
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[39][0].x, groundMap[0][6].y, ((tileSize)*scale), (tileSize)*scale });
	
	//table
	obstaclesLevel[insideHouse].emplace_back(Rectangle{ groundMap[35][0].x, groundMap[0][10].y + 18, 2 * ((tileSize + 2)*scale), 2 * (tileSize - 2)*scale });
}

Vector2 Physics::collisionObjectWall(const Vector2& Pos,Vector2 velocity,const float& deltaTime) {
	
	objectCoords();
	Rectangle nextPos = { Pos.x + velocity.x * deltaTime, Pos.y + velocity.y * deltaTime, tileSize * scale, tileSize * scale };

	for (const Rectangle& obstacle : obstaclesLevel[currentLevel])
	{
		if (CheckCollisionRecs(nextPos, obstacle)) {
			if (velocity.x != 0) {
				Rectangle testX = { Pos.x + velocity.x * deltaTime, Pos.y, tileSize * scale, tileSize * scale };
				if (CheckCollisionRecs(testX, obstacle)) {
					velocity.x = 0;
				}
			}

			if (velocity.y != 0) {
				Rectangle testY = { Pos.x, Pos.y + velocity.y * deltaTime, tileSize * scale, tileSize * scale };
				if (CheckCollisionRecs(testY, obstacle)) {
					velocity.y = 0;
				}
			}
		}
	}

	return velocity;
}

void Physics::draw() {
	if (IsKeyDown(KEY_O)) {
		for (const Rectangle& obstacle : obstaclesLevel[currentLevel]) {
			DrawRectangleLines(obstacle.x + tileSize * scale, obstacle.y + (tileSize * 2) * scale, obstacle.width, obstacle.height, WHITE);
		}
	}
}
