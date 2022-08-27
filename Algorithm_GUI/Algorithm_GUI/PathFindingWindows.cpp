#include "PathFindingWindows.h"
#include <Windows.h>

void PathFindingWindows::init(void)
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);
}

void PathFindingWindows::draw(void)
{
	BeginBatchDraw();
	cleardevice();

	for (int i = 0; i < ROW + 2; i++) {
		for (int j = 0; j < COL + 2; j++) {
			if (map[i][j].solid) {
				setfillcolor(CYAN);
				solidrectangle(BLOCK_LEN * j, BLOCK_LEN * i, BLOCK_LEN * (j + 1), BLOCK_LEN * (i + 1));
			}
			else {
				if (!map[i][j].visit) {
					rectangle(BLOCK_LEN * j, BLOCK_LEN * i, BLOCK_LEN * (j + 1), BLOCK_LEN * (i + 1));
				}
				else {
					setfillcolor(YELLOW);
					solidrectangle(BLOCK_LEN * j, BLOCK_LEN * i, BLOCK_LEN * (j + 1), BLOCK_LEN * (i + 1));
				}
			}

		}

	}

	dfs_button.draw();
	bfs_button.draw();

	EndBatchDraw();
}

void PathFindingWindows::solifyBlock_and_Start(void)
{
	ExMessage msg;

	while ( true ) {
		if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN) {
			if (msg.x < BLOCK_LEN * (COL + 2) && msg.y < BLOCK_LEN * (ROW + 2)) {
				map[msg.y / BLOCK_LEN][msg.x / BLOCK_LEN].solid = true;
			}
			else {
				if (bfs_button.isClick(&msg)) {
					constructGraph();
					BFS();
					break;
				}
				else if (dfs_button.isClick(&msg)) {
					constructGraph();
					DFS();
					break;
				}
			}

			draw(); // Update
		}
	}

	
}

void PathFindingWindows::constructGraph(void)
{
	// Construct a graph
	for (int i = 1; i < ROW + 1; i++) {
		for (int j = 1; j < COL + 1; j++) {
			if (!map[i - 1][j].solid) {
				map[i][j].nearBlock.push_back({ i - 1, j });
			}
			if (!map[i + 1][j].solid) {
				map[i][j].nearBlock.push_back({ i + 1, j });
			}
			if (!map[i][j - 1].solid) {
				map[i][j].nearBlock.push_back({ i, j - 1 });
			}
			if (!map[i][j + 1].solid) {
				map[i][j].nearBlock.push_back({ i, j + 1 });
			}
		}

	}
}

void PathFindingWindows::BFS(void)
{
}

bool PathFindingWindows::DFS(Block& _block)
{
	if (_block.solid) {
		return false;
	}
	_block.visit = true;
	draw();

	BeginBatchDraw();
	setfillcolor(RED);
	fillrectangle(BLOCK_LEN * _block.y, BLOCK_LEN * _block.x, BLOCK_LEN * (_block.y + 1), BLOCK_LEN * (_block.x + 1));
	EndBatchDraw();

	Sleep(10);
	if (_block.x == COL && _block.y == ROW) {
		return true; // ур╣╫жу╣Ц
	}

	if (_block.nearBlock.size() == 0) {
		return false;
	}
	for (auto& near_iter : _block.nearBlock) {
		if (!map[near_iter.first][near_iter.second].visit) {
			if (DFS(map[near_iter.first][near_iter.second])) {
				BeginBatchDraw();
				setfillcolor(RED);
				fillrectangle(BLOCK_LEN * _block.y, BLOCK_LEN * _block.x, BLOCK_LEN * (_block.y + 1), BLOCK_LEN * (_block.x + 1));
				EndBatchDraw();
				return true;
			}
		}
	}

	return false;
}

void PathFindingWindows::DFS(void)
{
	DFS(map[1][1]);
}

PathFindingWindows::PathFindingWindows(void)
{
	for (int i = 0; i < ROW + 2; i++) {

		map.push_back(vector<Block>());
		for (int j = 0; j < COL + 2; j++) {
			map.back().push_back(Block(i, j));
		}

	}

	for (int i = 0; i < ROW + 2; i++) {
		map[0][i].solid = true;
		map[i][0].solid = true;
		map[ROW + 1][i].solid = true;
		map[i][COL + 1].solid = true;
		// solify the margin
	}

	bfs_button = Button(700, 20, 900, 120, L"BFS");
	dfs_button = Button(700, 520, 900, 620, L"DFS");
}

void PathFindingWindows::start(void)
{
	init();
	draw();

	solifyBlock_and_Start();

	Sleep(100000);
}