#pragma once

#include "ofMain.h"
#include "point.h"

class Cell {
public:
	bool isLive_;
	Point<float> pixelSize_, pixelLocation_;

	enum stateColor {
		inactive = 150,
		active = 0
	};
	static constexpr Point<int> GRID_SIZE{ 24,24 };

	/**
	 * @brief sets up the pixel for drawing, and then draws it
	 *
	 * @param x The x index of the vector
	 * @param y The y index of the vector
	 * @param isFilled determines the style of the pixel
	 */
	void setupPixel(const int& x, const int& y, bool isFilled);

private:

	/**
	 * @brief Determines the visual look of a pixel based on a given number
	 * @param state changes the color of a pixel between stateColors
	 */
	void setStyle(bool state) const;

	/**
	 * @brief through the amount of pixels and size of the window,
	 * the height and width of a pixel is determined
	 *
	 * @return The calculated height and width for each pixel
	 */
	static Point<float> calculatePixelSize();
	
};
