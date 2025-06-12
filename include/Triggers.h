#pragma once
#include "Core.h"

class Triggers {
private:
	bool read;
	bool note;
	bool noteOpened;
	bool enterHouse;

	bool tv;
	bool tvOpened;
	bool tvWatching;

	bool book;
	bool bookOpened;
	bool bookWatching;

	bool exitHouse;

	bool telescope;
	bool telescopeOpened;
	bool telescopeWatching;

	int frames;
	int currentAnimFrame;
	int frameDelay;
	int frameCounter;
	unsigned int nextFrameDataOffset;
	std::vector<std::vector<Rectangle>> triggersLevel;

	Texture2D scroll;
	Texture2D paper;
	Texture2D e_Letter;
	Texture2D q_Letter;
	Texture2D animOsu;
	Texture2D texTv;
	Texture2D texTelescope;

	Texture2D bookDesk;

	Image image;
	Image animOsuImage;
public:
	Triggers();
	~Triggers();
	void triggerCoords();
	void collisionTrigger(const Vector2& Pos, std::function<void(Vector2)> changePos);
	void update(const float& deltaTime);
	void fadeInControl(const Vector2& Pos);
	void draw(const Vector2& Posconst, const Vector2& cameraPos);
};