#pragma once

#include "ofMain.h"
#include "point.h"

class Cell {
public:
	bool isLive_ = false;
	bool markedForUpdate_ = false;
	Rect<float> collider_;

	int count_ = 0;

	enum stateColor {
		inactive = 150,
		active = 0
	};

	static constexpr int GRID_SIZE{ 20 };

	/**
	 * @brief sets up the pixel for drawing, and then draws it
	 *
	 * @param x The x index of the vector
	 * @param y The y index of the vector
	 */
	void setupPixel(const int& x, const int& y);
	void drawNeighbours(); // DEBUG
	void updateCell();

	bool wasClickInside(int x, int y);

private:

	/**
	 * @brief Determines the visual look of a pixel based on a given number
	 */
	void setStyle() const;

	/**
	 * @brief through the amount of pixels and size of the window,
	 * the height and width of a pixel is determined
	 *
	 * @return The calculated height and width for each pixel
	 */
	static Point<float> calculatePixelSize();
};
