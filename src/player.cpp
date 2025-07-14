#include "player.h"

Player::Player(const float& Scale) :
    m_Speed(200.0f),
    m_Directions(DOWN),
    m_FrameIndex(0),
    m_FrameDelay(10),
    m_FrameDelayCount(0),
    m_FrameNum(7),
    m_SpawnPosX(1440),
    m_SpawnPosY(670),
    m_RectWidthPlayer(48.0f),
    m_RectHeightPlayer(64.0f),
    m_Pos({ m_SpawnPosX, m_SpawnPosY }),
    m_Velocity({ 0, 0 }),
    m_Scale(Scale)
{
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
    m_Velocity = { 0, 0 };

    if (IsKeyDown(KEY_A)) {
        m_Velocity.x = -m_Speed;
    }
    else if (IsKeyDown(KEY_D)) {
        m_Velocity.x = m_Speed;
    }

    if (IsKeyDown(KEY_S)) {
        m_Velocity.y = m_Speed;
    }
    if (IsKeyDown(KEY_W)) {
        m_Velocity.y = -m_Speed;
    }

    // Diagonal movement correction
    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W)) {
        m_Velocity.y = -m_Speed + 30;
    }
    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) {
        m_Velocity.y = m_Speed - 30;
    }
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W)) {
        m_Velocity.y = -m_Speed + 30;
    }
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_S)) {
        m_Velocity.y = m_Speed - 30;
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

void Player::Update(const float& deltaTime) {

    m_Pos.x += m_Velocity.x * deltaTime;
    m_Pos.y += m_Velocity.y * deltaTime;

    if (IsKeyPressed(KEY_B)) {
        std::cout << "Pos x: " << m_Pos.x << "  " << "Pos y: " << m_Pos.y << std::endl;
    }
}

void Player::Draw() {
    ++m_FrameDelayCount;
    if (m_FrameDelayCount > m_FrameDelay) {
        m_FrameDelayCount = 0;
        ++m_FrameIndex;
        m_FrameIndex %= m_FrameNum;
    }

    if (!m_Velocity.x && !m_Velocity.y) {
        if (IsKeyDown(KEY_T) && m_FrameIndex < DIR_COUNT) {
            DrawTextureRec(m_Idle, m_Movement_Rect[m_FrameIndex][DOWN], m_Pos, WHITE);
        }
        else {
            switch (m_Directions) {
            case DOWN:
                DrawTextureRec(m_Idle, m_Movement_Rect[DOWN][m_FrameIndex], m_Pos, WHITE);
                break;
            case UP:
                DrawTextureRec(m_Idle, m_Movement_Rect[UP][m_FrameIndex], m_Pos, WHITE);
                break;
            case LEFT_DOWN:
                DrawTextureRec(m_Idle, m_Movement_Rect[LEFT_DOWN][m_FrameIndex], m_Pos, WHITE);
                break;
            case LEFT_UP:
                DrawTextureRec(m_Idle, m_Movement_Rect[LEFT_UP][m_FrameIndex], m_Pos, WHITE);
                break;
            case RIGHT_UP:
                DrawTextureRec(m_Idle, m_Movement_Rect[RIGHT_UP][m_FrameIndex], m_Pos, WHITE);
                break;
            case RIGHT_DOWN:
                DrawTextureRec(m_Idle, m_Movement_Rect[RIGHT_DOWN][m_FrameIndex], m_Pos, WHITE);
                break;
            }
        }
    }
    else {
        switch (m_Directions) {
        case DOWN:
            DrawTextureRec(m_Walk, m_Movement_Rect[DOWN][m_FrameIndex], m_Pos, WHITE);
            break;
        case UP:
            DrawTextureRec(m_Walk, m_Movement_Rect[UP][m_FrameIndex], m_Pos, WHITE);
            break;
        case LEFT_DOWN:
            DrawTextureRec(m_Walk, m_Movement_Rect[LEFT_DOWN][m_FrameIndex], m_Pos, WHITE);
            break;
        case LEFT_UP:
            DrawTextureRec(m_Walk, m_Movement_Rect[LEFT_UP][m_FrameIndex], m_Pos, WHITE);
            break;
        case RIGHT_UP:
            DrawTextureRec(m_Walk, m_Movement_Rect[RIGHT_UP][m_FrameIndex], m_Pos, WHITE);
            break;
        case RIGHT_DOWN:
            DrawTextureRec(m_Walk, m_Movement_Rect[RIGHT_DOWN][m_FrameIndex], m_Pos, WHITE);
            break;
        }
    }
}

void Player::setVelocity(const Vector2& newVelocity) { 
    m_Velocity = newVelocity; 
}

Vector2 Player::getVelocity() const { 
    return m_Velocity; 
}

void Player::setPos(const Vector2& newPos) { 
    m_Pos = newPos; 
}

Vector2 Player::getPos() const { 
    return m_Pos; 
}