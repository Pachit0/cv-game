#include "texture_utils.h"

constexpr int FLAG_FLIPTEXTURE = 1;

Texture2D LoadFilteredTexture(const char* filePath) {
	Image image = LoadImage(filePath);
	Texture2D texture = LoadTextureFromImage(image);
	SetTextureFilter(texture, TEXTURE_FILTER_POINT);
	UnloadImage(image);
	return texture;
}

void DrawTextureRecEx(const Texture2D& texture, const Rectangle& srcRect, const Vector2& pos, float scale, float rotation, Vector2 origin, Color color) {
    Rectangle destRect = {
        pos.x,
        pos.y,
        srcRect.width * scale,
        srcRect.height * scale
    };

    DrawTexturePro(
        texture,
        srcRect,
        destRect,
        origin,
        rotation,
        color
    );
}
