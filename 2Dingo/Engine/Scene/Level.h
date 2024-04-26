#pragma once
#include <vector>

class Tile
{
public:
	Tile(char keyChar, bool isSolid = false) : KeyChar(keyChar), Solid(isSolid) {}
	~Tile() {}

	char KeyChar;
	bool Solid = false;
};

class Level
{
public:
	Level();
	~Level();


private:
	int mTileSize = 32;

	int mWidth = 30;
	int mHeight = 30;

	std::vector<std::vector<Tile>> mLevel;
};