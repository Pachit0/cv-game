#pragma once

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

class UIManager {
public:
    void Init();
    void Begin();
    void RenderMainMenu(bool& isPlaying, int screenWidth, int screenHeight);
    void End();
    void Shutdown();

};