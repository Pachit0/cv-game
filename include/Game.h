#pragma once

#include "player.h"
#include "tilemap.h"
#include "props.h"
#include "physics.h"
#include "Triggers.h"
#include "Camera.h"
#include "mouse.h"
#include "scenemanager.h"
#include "gameEnums.h"

class Game
{
private:
    void update();
    void draw();
    void init();
    void unload();

    void playerDrawPriorityLayer1();
    void playerDrawPriorityLayer2();

    Player* m_Player;
    Tilemap* m_Tilemap;
    MainCamera m_MainCamera;
    Physics* m_Physics;
    Triggers* m_Triggers;
    HandleMouse m_Mouse;
    Props* m_Props;
    UIManager* m_UI;
    SceneManager m_SceneManager;

    float m_DeltaTime;
    bool m_IsPlaying;

public:
    Game();
    ~Game();

    void run();

};
