#include "UIManager.h"

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
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Game Menu", nullptr, window_flags);

    ImGui::SetCursorPosX((screenWidth - 385) * 0.5f);
    ImGui::SetCursorPosY((screenHeight) * 0.5f);
    ImGui::SetWindowFontScale(5.0f);
    ImGui::Text("SickAssGame");
    ImGui::SetWindowFontScale(1.0f);


    ImGui::SetCursorPosY((screenHeight + 200) * 0.5f);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));   // color
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f)); // Hover color
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));  // Clicked color
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f); // rounding

    ImGui::SetCursorPosX((screenWidth - 300) * 0.5f);
    ImGui::SetWindowFontScale(3.0f);

    if (ImGui::Button("Start Game", ImVec2(300, 50))) {
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