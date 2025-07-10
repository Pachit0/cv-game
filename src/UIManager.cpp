#include "UIManager.h"

UIManager::UIManager()
{
    m_Image = LoadImage(RESOURCES_PATH "pop-ups/2-adventurer.png");
    ImageResize(&m_Image, m_Image.width * 1.67, m_Image.height * 1.30);
    m_Background = LoadTextureFromImage(m_Image);
    UnloadImage(m_Image);
}

UIManager::~UIManager()
{
    UnloadTexture(m_Background);
}

void UIManager::Init() {
	rlImGuiSetup(true);
}

void UIManager::Begin() {
    rlImGuiBegin();
}

void UIManager::RenderMainMenu(bool& isPlaying, int screenWidth, int screenHeight) {
    ImGui::SetNextWindowSize(ImVec2(screenWidth, screenHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground ;

    ImGui::Begin("Game Menu", nullptr, window_flags);
    DrawTexture(m_Background,0,0,WHITE);
    /*ImGui::SetCursorPosX((screenWidth - 500) * 0.5f);
    ImGui::SetCursorPosY((screenHeight - 100) * 0.5f);
    ImGui::SetWindowFontScale(5.0f);
    ImGui::Text("The adventurer");*/
    ImGui::SetWindowFontScale(1.0f);


    ImGui::SetCursorPosY((screenHeight + 100) * 0.5f);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.75f, 0.51f, 0.39f, 1.00f));   // color
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f)); // Hover color
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));  // Clicked color
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f); // rounding

    ImGui::SetCursorPosX((screenWidth - 285) * 0.5f);
    ImGui::SetWindowFontScale(3.0f);

    if (ImGui::Button("start", ImVec2(300, 50))) {
        isPlaying = true;
    }

    ImGui::SetWindowFontScale(1.0f);

    ImGui::PopStyleColor(3); // The value needs to be different for more pushStyleColors!!!
    ImGui::PopStyleVar();

    ImGui::End();
}

void UIManager::End() {
    rlImGuiEnd();
}

void UIManager::Shutdown() {
    rlImGuiShutdown();
}