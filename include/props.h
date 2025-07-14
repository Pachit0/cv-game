#pragma once
#include "Core.h"
#include "gameEnums.h"

class Props {
private:
	const float m_TileSize;
	const float m_Scale;
	const std::array<std::array<Rectangle, 30>, 60>& m_GroundMap;

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

public:
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

	Props(const float& TileSize, const float& Scale, const std::array<std::array<Rectangle, 30>, 60>& groundMap);
	~Props();

	void drawLayer1(Scene::Level currentLevel) const;
	void drawLayer2(Scene::Level currentLevel) const;
	bool underCheck(const Vector2& pos, const std::vector<Rectangle>& propsCoords);
	std::vector<Rectangle>& getCoordsLayer1(Scene::Level currentLevel);
	std::vector<Rectangle>& getCoordsLayer2(Scene::Level currentLevel);
	std::vector<propEntry> loadPropsFromJSON(const std::string& filename);
	void loadPropsCoordsFromJSON(const std::string& path);

private:
	std::vector<std::vector<std::vector<Rectangle>>> m_PropsCoords;
	nlohmann::json m_Data;
	std::ifstream m_File;
	std::vector<propEntry> m_AllProps;
};
