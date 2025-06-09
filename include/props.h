#pragma once
#include "Core.h"

class Props {
private:
	Image image;
	Texture2D board;
	Texture2D house;
	Texture2D campfire;
	Texture2D lamp[4];
	Texture2D table;
	Texture2D tree;
	Texture2D treeRiver;
	Texture2D tree3;
	Texture2D cutTree;

	std::vector<Rectangle> propsCoordsLayer1;
	std::vector<Rectangle> propsCoordsLayer2;

public:
	Props();
	~Props();

	void drawLayer1() const;
	void drawLayer2() const;
	bool underCheck(const Vector2& pos, const std::vector<Rectangle>& propsCoords);
	std::vector<Rectangle>& getCoordsLayer1();
	std::vector<Rectangle>& getCoordsLayer2();
};