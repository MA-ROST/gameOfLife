#include "gameManager.h"

#include <ObjectArray.h>

void GameManager::setup()
{
	for (auto& cellRow : cells_) {
		for (auto& cell : cellRow) {
			const int ran = rand() % 2;
			cell.isLive_ = ran;
		}
	}
}

void GameManager::drawCells()
{
	for (int x = 0; x < Cell::GRID_SIZE.x; ++x) {
		for (int y = 0; y < Cell::GRID_SIZE.y; ++y) {
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
	cellFollowsRules(row - 1, column - 1);
	cellFollowsRules(row - 1, column);
	cellFollowsRules(row - 1, column + 1);
	cellFollowsRules(row,	  column - 1);
	// DO NOT CHECK THE SAME SPOT WE ARE ON (row,column) ....
	cellFollowsRules(row,	  column + 1);
	cellFollowsRules(row + 1, column - 1);
	cellFollowsRules(row + 1, column);
	cellFollowsRules(row + 1, column - 1);
}

void GameManager::cellFollowsRules(const int row, const int col)
{
	int r = row;
	int c = col;
	int count = 0;
	r = row - 1;
	if (rowInBound (r)) {
		isInBounds(col - 1); // Check spot #1
		isInBounds(col);     // Check spot #2
		isInBounds(col + 1); // Check spot #3
	}
bool GameManager::isCellLive(const int row, const int column)
{
	if (cellInBound (row, column) && cells_[row][column].isLive_) { return true; }
	return false;
}

int GameManager::countLiveNeighbours(const int row, const int column)
{
	int count = 0;
	if (isCellLive(row - 1, column - 1)) count++;
	if (isCellLive(row - 1, column)) count++;
	if (isCellLive(row - 1, column + 1)) count++;
	if (isCellLive(row, column - 1)) count++;
	// DO NOT CHECK THE SAME SPOT WE ARE ON (row,column) ....
	if (isCellLive(row, column + 1)) count++;
	if (isCellLive(row + 1, column - 1)) count++;
	if (isCellLive(row + 1, column)) count++;
	if (isCellLive(row + 1, column - 1)) count++;

	return count;

}

bool GameManager::rowInBound(int row)
{
	if (row < 0)    return false;               // Before first row
	if (row >= Cell::GRID_SIZE.x) return false; // After last row
	return true;                                // Valid row
}

bool GameManager::colInBound(int col)
{
	if (col < 0) return false;					// Before first column
	if (col >= Cell::GRID_SIZE.y) return false; // After last column
	return true;                                // Valid row
}

bool GameManager::cellInBound(int row, int col)
{
	if (rowInBound(row) && colInBound(col)) return true;
	return false;
}

bool GameManager::isInBounds(const int col)
{
	if (colInBound(col))
	{
		std::cout << col << " is valid\n";
		return true;
	}
	return false;
}
