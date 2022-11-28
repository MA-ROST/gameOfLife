#pragma once
#include <array>
#include <vector>

#include "cell.h"

class GameManager {
	array<array<Cell, Cell::GRID_SIZE.x>, Cell::GRID_SIZE.y> cells_;
	
public:
	void setup();
	void drawCells();

	void neighbourLogic(int row, int column);
	void checkNeighbours(int row, int column);
	void cellFollowsRules(int row, int col);
	int countLiveNeighbours(int row, int column);
	bool isCellLive(int row, int column);

	bool rowInBound(int row);
	bool colInBound(int col);
	bool isInBounds(int col);
	bool cellInBound(int row, int col);
	
};
