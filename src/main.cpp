#include "Game.h"

int main() {
    InitWindow(screenWidth, screenHeight, "sickAssGame");
    
    Game game;
    game.ui.Init();

    bool isPlaying = false;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();


        if (isPlaying) {
            game.Update(deltaTime);
        }

        BeginDrawing();

        game.ui.Begin();

        if (!isPlaying) {
            game.ui.RenderMainMenu(isPlaying, screenWidth, screenHeight);
        }

        game.ui.End();

        if (isPlaying) {
            BeginMode2D(game.camera_c.getCamera());
            game.Draw();
            EndMode2D();
        }

        EndDrawing();
    }

    game.ui.Shutdown();
    CloseWindow();

    return 0;
}