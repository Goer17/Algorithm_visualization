#pragma once
#include <easyx.h>
#include <vector>
#include "Button.h"

using namespace std;

#define WIN_WIDTH 960
#define WIN_HEIGHT 640

#define ROW 30
#define COL 30
#define BLOCK_LEN 20

class Block
{
public:
	int x; // X-coordinate
	int y; // Y-coordinate
	bool visit; // Whether to be visited
	bool solid; // Whether to be solified

	vector<pair<int, int>> nearBlock; // Store the coordinate of those blocks that near this block

	Block(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
		this->visit = false;
		this->solid = false;
	}
};

class PathFindingWindows
{
private:

	vector<vector<Block>> map; // The showing map

	Button bfs_button; // BFS
	Button dfs_button; // DFS
	
	
	void init(void); // To initialize the main page

	void draw(void); // To draw the page according to map

	void solifyBlock_and_Start(void); // Solify the blocks where users click

	void BFS(void); // Breadth First Search 

	void DFS(void); // Deep First Search


public:

	PathFindingWindows(void);

	void start(void);

};