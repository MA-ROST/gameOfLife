#pragma once
#include <array>
#include <vector>

#include "cell.h"

class GameManager {
	array<array<Cell, Cell::GRID_SIZE>, Cell::GRID_SIZE> cells_;

	bool isInPlay_ = true;
	
public:
	void setup();
	void pause();
	void showNeighbours(int x, int y);
	
	void drawCells();
	void updateCells(); // Update the cells after all are checked
	void cellFollowsRules(int row, int col);
	int countLiveNeighbours(int row, int column);
	bool isCellLive(int row, int column);

	bool rowInBound(int row);
	bool colInBound(int col);
	bool isInBounds(int col);
	bool cellInBound(int row, int col);

	void randomizeGrid();

	void mouseDragged(int x, int y, int button);
	Point<int> getClicked(int x, int y);
	
};


