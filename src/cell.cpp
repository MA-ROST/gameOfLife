#include "cell.h"

void Cell::setupPixel(const int& x, const int& y, bool isFilled)
{
	pixelSize_ = calculatePixelSize();
	setStyle(isFilled);
	ofDrawRectangle(pixelSize_.x * x, pixelSize_.y * y, pixelSize_.x, pixelSize_.y);
}

void Cell::setStyle(bool state) const
{
	ofFill();
	switch (state) {
	case true:
		ofSetColor(active);
		break;
	default:
		ofNoFill();
		ofSetColor(inactive);
		break;
	}

}

Point<float> Cell::calculatePixelSize()
{
	Point <float> output{
		static_cast <float> (ofGetWidth()) / GRID_SIZE.x,
		static_cast <float> (ofGetHeight()) / GRID_SIZE.y
	};

	return output;
}
