#pragma once
#include "core.h"

Texture2D LoadFilteredTexture(const char* filePath);
void DrawTextureRecEx(const Texture2D& texture,const Rectangle& srcRect,const Vector2& pos, float scale, float rotation = 0.0f, Vector2 origin = { 0,0 }, Color color = WHITE);
