#pragma once

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

class UIManager {
private:
    Image m_Image;
    Texture2D m_Background;
public:
    UIManager();
    ~UIManager();
    void Init();
    void Begin();
    void RenderMainMenu(bool& isPlaying, int screenWidth, int screenHeight);
    void End();
    void Shutdown();
};