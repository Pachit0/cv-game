#pragma once

#include "player.h"
#include "tile_map.h"
#include "props.h"
#include "physics.h"
#include "triggers_manager.h"
#include "camera.h"
#include "mouse.h"
#include "scene_manager.h"
#include "game_enums.h"
#include "ui_manager.h"

class Game
{
private:
    void update();
    void draw();
    void init();
    void unload();

    void playerDrawPriorityLayer1();
    void playerDrawPriorityLayer2();

    std::unique_ptr<Player> m_Player;
    std::unique_ptr<Tilemap> m_Tilemap;
    std::unique_ptr<Physics> m_Physics;
    std::unique_ptr<Triggers> m_Triggers;
    std::unique_ptr<Props> m_Props;
    std::unique_ptr<UIManager> m_UI;
    std::unique_ptr<MainCamera> m_MainCamera;
    std::unique_ptr<HandleMouse> m_Mouse;
    SceneManager m_SceneManager;

    float m_DeltaTime;
    bool m_IsPlaying;

    const int m_ScreenHeight;
    const int m_ScreenWidth;

    const int m_BaseHeight;
    const int m_BaseWidth;
    const float m_Scale;
    const float m_TileSize;
public:
    Game();
    ~Game();

    void run();
};
