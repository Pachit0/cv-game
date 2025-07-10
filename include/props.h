#pragma once
#include "Core.h"

struct propEntry {
	std::string Level;
	std::string Layer;
	int TileX;
	int TileY;
	int WidthTile;
	int HeightTile;
};

enum propsLayer {
	first,
	second,
	third
};

class Props {
private:
	Image m_Image;
	Texture2D m_Board;
	Texture2D m_House;
	Texture2D m_Campfire;
	Texture2D m_Lamp[4];
	Texture2D m_Table;
	Texture2D m_Tree;
	Texture2D m_TreeRiver;
	Texture2D m_Tree3;
	Texture2D m_CutTree;
	Texture2D m_InsideChair;
	Texture2D m_Book;
	Texture2D m_Telescope;

	std::vector<std::vector<std::vector<Rectangle>>> m_PropsCoords;
	nlohmann::json m_Data;
	std::ifstream m_File;
	std::vector<propEntry> m_AllProps;

public:
	Props();
	~Props();

	void drawLayer1() const;
	void drawLayer2() const;
	bool underCheck(const Vector2& pos, const std::vector<Rectangle>& propsCoords);
	std::vector<Rectangle>& getCoordsLayer1();
	std::vector<Rectangle>& getCoordsLayer2();
	std::vector<propEntry> loadPropsFromJSON(const std::string& filename);
	void loadPropsCoordsFromJSON(const std::string& path);
};
