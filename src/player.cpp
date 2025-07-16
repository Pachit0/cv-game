#include "player.h"

Player::Player(const float& Scale, const float& TileSize) :
    m_Directions(DOWN),
    m_FrameIndex(0),
    m_FrameDelay(10),
    m_FrameDelayCount(0),
    m_FrameNum(7),
    m_SpawnPosX(1440),
    m_SpawnPosY(670),
    m_RectWidthPlayer(48.0f),
    m_RectHeightPlayer(64.0f),
    m_Scale(Scale),
    Entity(TileSize)
{

    setEntityPosition({ m_SpawnPosX, m_SpawnPosY });
    setEntityVelocity({ 0, 0 });
    setEntitySpeed(200.0f);

    m_Image = LoadImage(RESOURCES_PATH "TheAdventurer/Idle/idle.png");
    ImageResize(&m_Image, 384 * 3, 384 * 3);
    m_Idle = LoadTextureFromImage(m_Image);
    UnloadImage(m_Image);

    m_Image = LoadImage(RESOURCES_PATH "TheAdventurer/Walk/walk.png");
    ImageResize(&m_Image, 384 * 3, 384 * 3);
    m_Walk = LoadTextureFromImage(m_Image);
    UnloadImage(m_Image);

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            m_Movement_Rect[i][j] = { j * m_RectWidthPlayer * m_Scale, i * m_RectHeightPlayer * m_Scale, m_RectWidthPlayer * m_Scale, m_RectHeightPlayer * m_Scale };
        }
    }
}

Player::~Player() {
    UnloadTexture(m_Idle);
    UnloadTexture(m_Walk);
}

void Player::inputHandling() {
    setEntityVelocity({ 0, 0 });

    if (IsKeyDown(KEY_A)) {
        getEntityVelocity().x = -getEntitySpeed();
    }
    else if (IsKeyDown(KEY_D)) {
        getEntityVelocity().x = getEntitySpeed();
    }

    if (IsKeyDown(KEY_S)) {
        getEntityVelocity().y = getEntitySpeed();
    }
    if (IsKeyDown(KEY_W)) {
        getEntityVelocity().y = -getEntitySpeed();
    }

    // Diagonal movement correction
    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W)) {
        getEntityVelocity().y = -getEntitySpeed() + 30;
    }
    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) {
        getEntityVelocity().y = getEntitySpeed() - 30;
    }
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W)) {
        getEntityVelocity().y = -getEntitySpeed() + 30;
    }
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_S)) {
        getEntityVelocity().y = getEntitySpeed() - 30;
    }
}

void Player::handleCurrentDirection() {
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) {
        m_Directions = LEFT_UP;
    }
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) {
        m_Directions = RIGHT_UP;
    }
    else if (IsKeyDown(KEY_A)) {
        m_Directions = LEFT_DOWN;
    }
    else if (IsKeyDown(KEY_D)) {
        m_Directions = RIGHT_DOWN;
    }
    else if (IsKeyDown(KEY_W)) {
        m_Directions = UP;
    }
    else if (IsKeyDown(KEY_S)) {
        m_Directions = DOWN;
    }
}

void Player::update(const float& deltaTime) {

    Entity::update(deltaTime);

    if (IsKeyPressed(KEY_B)) {
        std::cout << "Pos x: " << getEntityPosition().x << "  " << "Pos y: " << getEntityPosition().y << std::endl;
    }

}

/* tried some stuff to fix the bug when entering a new area | will do later
void Player::checkScenePouse(Scene::FadeState currentFadeState) {
    if (currentFadeState == Scene::FadeState::FADE_HOLD || currentFadeState == Scene::FadeState::FADE_IN) {
        setEntityVelocity({ 0,0 });
    }
}*/

void Player::draw() {
    ++m_FrameDelayCount;
    if (m_FrameDelayCount > m_FrameDelay) {
        m_FrameDelayCount = 0;
        ++m_FrameIndex;
        m_FrameIndex %= m_FrameNum;
    }

    if (!getEntityVelocity().x && !getEntityVelocity().y) {
        if (IsKeyDown(KEY_T) && m_FrameIndex < DIR_COUNT) {
            DrawTextureRec(m_Idle, m_Movement_Rect[m_FrameIndex][DOWN], getEntityPosition(), WHITE);
        }
        else {
            switch (m_Directions) {
            case DOWN:
                DrawTextureRec(m_Idle, m_Movement_Rect[DOWN][m_FrameIndex], getEntityPosition(), WHITE);
                break;
            case UP:
                DrawTextureRec(m_Idle, m_Movement_Rect[UP][m_FrameIndex], getEntityPosition(), WHITE);
                break;
            case LEFT_DOWN:
                DrawTextureRec(m_Idle, m_Movement_Rect[LEFT_DOWN][m_FrameIndex], getEntityPosition(), WHITE);
                break;
            case LEFT_UP:
                DrawTextureRec(m_Idle, m_Movement_Rect[LEFT_UP][m_FrameIndex], getEntityPosition(), WHITE);
                break;
            case RIGHT_UP:
                DrawTextureRec(m_Idle, m_Movement_Rect[RIGHT_UP][m_FrameIndex], getEntityPosition(), WHITE);
                break;
            case RIGHT_DOWN:
                DrawTextureRec(m_Idle, m_Movement_Rect[RIGHT_DOWN][m_FrameIndex], getEntityPosition(), WHITE);
                break;
            }
        }
    }
    else {
        switch (m_Directions) {
        case DOWN:
            DrawTextureRec(m_Walk, m_Movement_Rect[DOWN][m_FrameIndex], getEntityPosition(), WHITE);
            break;
        case UP:
            DrawTextureRec(m_Walk, m_Movement_Rect[UP][m_FrameIndex], getEntityPosition(), WHITE);
            break;
        case LEFT_DOWN:
            DrawTextureRec(m_Walk, m_Movement_Rect[LEFT_DOWN][m_FrameIndex], getEntityPosition(), WHITE);
            break;
        case LEFT_UP:
            DrawTextureRec(m_Walk, m_Movement_Rect[LEFT_UP][m_FrameIndex], getEntityPosition(), WHITE);
            break;
        case RIGHT_UP:
            DrawTextureRec(m_Walk, m_Movement_Rect[RIGHT_UP][m_FrameIndex], getEntityPosition(), WHITE);
            break;
        case RIGHT_DOWN:
            DrawTextureRec(m_Walk, m_Movement_Rect[RIGHT_DOWN][m_FrameIndex], getEntityPosition(), WHITE);
            break;
        }
    }

    Entity::draw();
}