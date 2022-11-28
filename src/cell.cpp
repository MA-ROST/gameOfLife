#include "cell.h"

void Cell::setupPixel(const int& x, const int& y)
{
	pixelSize_ = calculatePixelSize();
	setStyle();
	ofDrawRectangle(pixelSize_.x * x, pixelSize_.y * y, pixelSize_.x, pixelSize_.y);
}

void Cell::setStyle() const
{
	ofFill();
	switch (isLive_) {
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
