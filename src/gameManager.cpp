#include "gameManager.h"

#include <ObjectArray.h>

void GameManager::drawCells()
{
	for (int x = 0; x < Cell::GRID_SIZE.x; ++x) {
		for (int y = 0; y < Cell::GRID_SIZE.y; ++y) {
			cells_[x][y].setupPixel(x, y, false);
		}
	}
}

void GameManager::neighbourLogic(int row, int column)
{
	if (cells_[row][column].isLive_) {
		checkNeighbours(row, column);
	}
	else {
		checkNeighbours(row, column);
	}
}

void GameManager::checkNeighbours(int row, int column)
{
	// spots to check      coordinates of those spots
	// +---+---+---+    +---------+---------+---------+
	// | 1 | 2 | 3 |    | r-1,c-1 | r-1,c   | r-1,c+1 |
	// +---+---+---+    +---------+---------+---------+
	// | 4 | X | 5 |    | r  ,c-1 | r  ,c   | r  ,c+1 |
	// +---+---+---+    +---------+---------+---------+
	// | 6 | 7 | 8 |    | r+1,c-1 | r+1,c   | r+1,c+1 |
	// +---+---+---+    +---------+---------+---------+
	cellFollowsRules(cells_[row - 1][column - 1]);
	cellFollowsRules(cells_[row - 1][column]);
	cellFollowsRules(cells_[row - 1][column + 1]);
	cellFollowsRules(cells_[row][column - 1]);
	// DO NOT CHECK THE SAME SPOT WE ARE ON (row,column) ....
	cellFollowsRules(cells_[row][column + 1]);
	cellFollowsRules(cells_[row + 1][column - 1]);
	cellFollowsRules(cells_[row + 1][column]);
	cellFollowsRules(cells_[row + 1][column - 1]);
}

void GameManager::cellFollowsRules(Cell& cell)
{
	// 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.

	// 2. Any live cell with two or three live neighbours lives on to the next generation.
	// 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
	// 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
}
