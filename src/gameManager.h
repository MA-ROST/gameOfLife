﻿#pragma once
#include <array>
#include <vector>

#include "ofxGui.h"
#include "cell.h"

class GameManager {
	vector<vector<Cell>> cells_;
	ofTrueTypeFont font_;

	int updateInterval_ = 15;
	int generation_     = 0;
	bool isPaused_     = false;
	bool wasClickTrue_ = false; // Used only on click events

	ofxToggle menuPauseBtn_;
	ofxButton randomize_;
	ofxButton clear_;
	ofxButton push_;
	ofxButton pop_;
	ofxLabel genLbl_;
	ofxPanel settingPnl_;

public:
	void setupCells();
	void setup();
	void setupGui();

	void draw();
	/**
	 * @brief Draw each cell, every 4th frame should run cellFollowsRules();
	 */
	void drawCells();
	/**
	 * @brief update all of the cells after they have been drawn.
	 */
	void updateCells();
	/**
	 * @brief Check if the cell is still valid to be live or dead
	 * @param row the 1st index of cells_
	 * @param col the 2nd index of cells_
	 */
	void cellFollowsRules(int row, int col);
	/**
	 * @brief Find out how many neighbouring cells are alive
	 * @param row the 1st index of cells_
	 * @param col the 2nd index of cells_
	 * @return How many neighbouring cells were found alive
	 */
	int countLiveNeighbours(int row, int col);
	/**
	 * @brief Checks the array to make sure that a given object is valid, halting OOB errors
	 * @param row the 1st index of cells_
	 * @param col the 2nd index of cells_
	 * @return returns true if the cell is in bounds and live
	 */
	bool isCellLive(int row, int col);

	/**
	 * @brief Checks the array to make sure that a given object is valid, halting OOB errors
	 * @param row the 1st index of cells_
	 * @return If the row is within the bounds of the array
	 */
	bool rowInBound(int row);
	/**
	 * @brief Checks the array to make sure that a given object is valid, halting OOB errors
	 * @param col the 2nd index of cells_
	 * @return If the col is within the bounds of the array
	 */
	bool colInBound(int col);
	/**
	 * @brief Checks the array to make sure that a given object is valid, halting OOB errors
	 * @param row the 1st index of cells_
	 * @param col the 2nd index of cells_
	 * @return If the cell is in bound
	 */
	bool cellInBound(int row, int col);
	void toggleCell(Point<int> mouseCoord);

	/**
	 * @brief Runs a drag event where
	 * @param x Where the mouse was clicked on a horizontal axis
	 * @param y Where the mouse was clicked on a vertical axis
	 */
	void mouseDragged(int x, int y);
	void mousePressed(int x, int y);
	void mouseReleased();
	/**
	 * @brief Determine what cell was clicked
	 * @param x Where the mouse was clicked on a horizontal axis
	 * @param y Where the mouse was clicked on a vertical axis
	 * @return which cell was clicked
	 */
	Point<int> getClicked(int x, int y);

	/**
	 * @brief Regenerate the grid so random amounts are alive or dead
	 */
	void randomizeGrid();
	void clearGrid();

	void push();
	void pop();
};

