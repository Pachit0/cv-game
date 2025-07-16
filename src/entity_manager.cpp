#include "entity_manager.h"

Entity::Entity(const float& TileSize) : m_TileSize(TileSize) {}

Entity::~Entity() {}

void Entity::update(const float& deltaTime) {

    m_Position.x += m_Velocity.x * deltaTime;
    m_Position.y += m_Velocity.y * deltaTime;

}

void Entity::draw() {
    if (IsKeyDown(KEY_V)) {
        DrawRectangleV(m_Position, { m_TileSize * 2, m_TileSize * 2 }, RED); //placeholder
    }
}

void Entity::setEntityVelocity(const Vector2& newVelocity) {
    m_Velocity = newVelocity;
}

Vector2 Entity::getEntityVelocity() const { // read only
    return m_Velocity;
}

Vector2& Entity::getEntityVelocity() { // modifiable
    return m_Velocity;
}

void Entity::setEntityPosition(const Vector2& newPosition) {
    m_Position = newPosition;
}

Vector2 Entity::getEntityPosition() const {
    return m_Position;
}

void Entity::setEntitySpeed(const float& newSpeed) {
    m_Speed = newSpeed;
}

float Entity::getEntitySpeed() {
    return m_Speed;
}