#include "gameManager.h"

#include <ObjectArray.h>

void GameManager::setup()
{
	font_.load("arial.ttf", 32);
	randomizeGrid();
}

void GameManager::pause()
{
	isInPlay_ = isInPlay_ ? false : true;
}

void GameManager::draw()
{
	drawCells();
	if (!isInPlay_) {
		ofFill();
		ofSetColor(ofColor::black, 100);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		ofSetColor(ofColor::red);
		ofDrawBitmapString("PAUSED", 100, 100);
		font_.drawString("PAUSED", 200, 200);
	}
}


void GameManager::drawCells()
{
	for (int x = 0; x < Cell::GRID_SIZE; ++x) {
		for (int y = 0; y < Cell::GRID_SIZE; ++y) {
			cells_[x][y].setupPixel(x, y);
			if (ofGetFrameNum() % updateInterval_ == 0 && isInPlay_) {
				cellFollowsRules(x, y);
			}
		}
	}

	ofSetColor(ofColor::red);
	ofDrawBitmapString("Generation: " + std::to_string(generation_), 0, 100);

	if (ofGetFrameNum() % updateInterval_ == 0 && isInPlay_) {
		updateCells();
	}
}

void GameManager::updateCells()
{
	for (auto& cellRow : cells_) {
		for (auto& cell : cellRow) {
			if (cell.markedForUpdate_) {
				cell.updateCell();
			}
		}
	}

	generation_++;
}

void GameManager::cellFollowsRules(const int row, const int col)
{
	const int r = row;
	const int c = col;

	if (cellInBound(r, c)) {
		const int count = countLiveNeighbours(r, c);
		cells_[r][c].count_ = count;

		if (cells_[r][c].isLive_) {
			// 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
			// 2. Any live cell with two or three live neighbours lives on to the next generation.
			// 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
			if (count == 0 || count < 2 || count > 3) {
				cells_[r][c].markedForUpdate_ = true;
			}
		}
		else {
			// 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
			if (count == 3) cells_[r][c].markedForUpdate_ = true;
		}
	}
}

bool GameManager::isCellLive(const int row, const int col)
{
	if (cellInBound(row, col) && cells_[row][col].isLive_)  return true;
	return false;
}

int GameManager::countLiveNeighbours(const int row, const int col)
{
	int count = 0;

	count += isCellLive(row - 1, col - 1);
	count += isCellLive(row - 1, col);
	count += isCellLive(row - 1, col + 1);
	count += isCellLive(row, col - 1); //**
	// DO NOT CHECK THE SAME SPOT WE ARE ON (row,column) ....
	count += isCellLive(row, col + 1);
	count += isCellLive(row + 1, col - 1);
	count += isCellLive(row + 1, col);
	count += isCellLive(row + 1, col + 1);
	
	return count;
}

bool GameManager::rowInBound(const int row)
{
	if (row < 0) return false;					// Before first row
	if (row >= Cell::GRID_SIZE) return false;	// After last row
	return true; // Valid row
}

bool GameManager::colInBound(const int col)
{
	if (col < 0) return false;					// Before first column
	if (col >= Cell::GRID_SIZE) return false;   // After last column
	return true;                                // Valid row
}

bool GameManager::cellInBound(const int row, const int col)
{
	if (rowInBound(row) && colInBound(col)) return true;
	return false;
}

void GameManager::mouseDragged(const int x, const int y)
{
	const Point<int> mouseCoord = getClicked(x, y);

	if (cellInBound(mouseCoord.x, mouseCoord.y))
	{
		cells_[mouseCoord.x][mouseCoord.y].isLive_ = true;
	}

}

Point<int> GameManager::getClicked(const int x, const int y)
{
	for (int a = 0; a < Cell::GRID_SIZE; ++a) {
		for (int b = 0; b < Cell::GRID_SIZE; ++b) {
			if (cells_[a][b].wasClickInside(x, y)) {
				return { a,b };
			}
		}
	}
}

void GameManager::randomizeGrid()
{
	for (auto& cellRow : cells_) {
		for (auto& cell : cellRow) {
			// Randomly get 0 or 1
			const int ran = rand() % 2;
			cell.isLive_ = ran;
		}
	}
}
