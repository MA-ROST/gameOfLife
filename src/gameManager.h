#pragma once
#include <array>
#include <vector>

#include "cell.h"

class GameManager {
	array<array<Cell, Cell::GRID_SIZE.x>, Cell::GRID_SIZE.y> cells_;

	
public:
	void drawCells();

	void neighbourLogic(int row, int column);
	void checkNeighbours(int row, int column);
	void cellFollowsRules(Cell& cell);
	void cellFollowsRules(int row, int col);
	int countLiveNeighbours(int row, int column);
	bool isCellLive(int row, int column);

	bool rowInBound(int row);
	bool colInBound(int col);
	bool isInBounds(int col);
	bool cellInBound(int row, int col);
	
};



/**
 * 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 * 2. Any live cell with two or three live neighbours lives on to the next generation.
 * 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
 * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 */
