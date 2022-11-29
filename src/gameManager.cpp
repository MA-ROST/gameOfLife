#include "gameManager.h"

#include <ObjectArray.h>

void GameManager::setup()
{
	randomizeGrid();
}

void GameManager::pause()
{
	if (isInPlay_) isInPlay_ = false;
	else isInPlay_ = true;
}

void GameManager::showNeighbours(int x, int y)
{
	Point<int> coord = getClicked(x, y);

	cells_[coord.x - 1][coord.y - 1].testing_ = isCellLive(coord.x - 1, coord.y - 1);
	cells_[coord.x - 1][coord.y].testing_ = isCellLive(coord.x - 1, coord.y);
	cells_[coord.x - 1][coord.y + 1].testing_ = isCellLive(coord.x - 1, coord.y + 1);

	cells_[coord.x][coord.y - 1].testing_ = isCellLive(coord.x, coord.y - 1);
	// DO NOT CHECK THE SAME SPOT WE ARE ON (row,column) ....
	cells_[coord.x][coord.y+1].testing_ = isCellLive(coord.x, coord.y+1);

	cells_[coord.x + 1][coord.y - 1].testing_ = isCellLive(coord.x + 1, coord.y - 1);
	cells_[coord.x + 1][coord.y].testing_ = isCellLive(coord.x + 1, coord.y);
	cells_[coord.x + 1][coord.y + 1].testing_ = isCellLive(coord.x + 1, coord.y + 1);
}

void GameManager::drawCells()
{
	for (int x = 0; x < Cell::GRID_SIZE; ++x) {
		for (int y = 0; y < Cell::GRID_SIZE; ++y) {
			cells_[x][y].setupPixel(x, y);
			cells_[x][y].drawNeighbours();
			if (ofGetFrameNum() % 4 == 0 && isInPlay_) {
				cellFollowsRules(x, y);
			}
		}
	}
	cout << "fin \n";
	
}

void GameManager::cellFollowsRules(const int row, const int col)
{
	const int r = row;
	const int c = col;

	if (cellInBound (r, c)) {
		int count = countLiveNeighbours(r, c);
		cells_[r][c].count_ = count;
		
		if (cells_[r][c].isLive_) {
			// 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
			// 2. Any live cell with two or three live neighbours lives on to the next generation.
			// 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
			if (count == 0 || count < 2 || count > 3) {
				cells_[r][c].isLive_ = false; // Change to mark for change
			}
		}
		else {
			// 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
			if (count == 3) cells_[r][c].isLive_ = true; // Change to mark for change
		}
	}
}

bool GameManager::isCellLive(const int row, const int column)
{
	if (cellInBound (row, column) && cells_[row][column].isLive_)  return true; 
	return false;
}

int GameManager::countLiveNeighbours(const int row, const int column)
{
	int count = 0;

	count += isCellLive(row - 1, column - 1);
	count += isCellLive(row - 1, column);
	count += isCellLive(row - 1, column + 1);

	count += isCellLive(row, column - 1); //**
	// DO NOT CHECK THE SAME SPOT WE ARE ON (row,column) ....
	count += isCellLive(row, column + 1);

	count += isCellLive(row + 1, column - 1);
	count += isCellLive(row + 1, column);
	count += isCellLive(row + 1, column + 1);

	//std::cout << row << " " << column << " has " << count << "/7 live neighbours\n";
	return count;
}

bool GameManager::rowInBound(int row)
{
	if (row < 0)    return false;               // Before first row
	if (row >= Cell::GRID_SIZE) return false; // After last row
	return true;                                // Valid row
}

bool GameManager::colInBound(int col)
{
	if (col < 0) return false;					// Before first column
	if (col >= Cell::GRID_SIZE) return false; // After last column
	return true;                                // Valid row
}

bool GameManager::cellInBound(int row, int col)
{
	if (rowInBound(row) && colInBound(col)) return true;
	return false;
}

bool GameManager::isInBounds(const int col)
{
	if (colInBound(col)) return true;
	return false;
}

void GameManager::randomizeGrid()
{
	for (auto& cellRow : cells_) {
		for (auto& cell : cellRow) {
			const int ran = rand() % 2;
			cell.isLive_ = ran;
		}
	}
}

void GameManager::mouseDragged(int x, int y, int button)
{
	Point<int> mouseCoord = getClicked(x,y);

	cells_[mouseCoord.x][mouseCoord.y].isLive_ = true;
}

Point<int> GameManager::getClicked(int x, int y)
{

	for (int a = 0; a < Cell::GRID_SIZE; ++a) {
		for (int b = 0; b < Cell::GRID_SIZE; ++b) {
			if (cells_[a][b].wasClickInside(x, y)) {
				return { a,b };
			}
		}
	}
}
