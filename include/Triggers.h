#pragma once
#include "Core.h"

class Triggers {
private:
	bool m_Read;
	bool m_Note;
	bool m_NoteOpened;
	bool m_EnterHouse;

	bool m_Tv;
	bool m_TvOpened;
	bool m_TvWatching;

	bool m_Book;
	bool m_BookOpened;
	bool m_BookWatching;

	bool m_ExitHouse;

	bool m_Telescope;
	bool m_TelescopeOpened;
	bool m_TelescopeWatching;

	int m_Frames;
	int m_CurrentAnimFrame;
	int m_FrameDelay;
	int m_FrameCounter;
	unsigned int m_NextFrameDataOffset;
	std::vector<std::vector<Rectangle>> m_TriggersLevel;

	Texture2D m_Scroll;
	Texture2D m_Paper;
	Texture2D m_E_Letter;
	Texture2D m_Q_Letter;
	Texture2D m_AnimOsu;
	Texture2D m_TexTv;
	Texture2D m_TexTelescope;

	Texture2D m_BookDesk;

	Image m_Image;
	Image m_AnimOsuImage;

public:
	Triggers();
	~Triggers();

	void triggerCoords();
	void collisionTrigger(const Vector2& Pos, std::function<void(Vector2)> changePos);
	void update(const float& deltaTime);
	void fadeInControl(const Vector2& Pos);
	void draw(const Vector2& Posconst, const Vector2& cameraPos);
};
