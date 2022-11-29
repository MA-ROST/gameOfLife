#include "cell.h"

void Cell::setupPixel(const int& x, const int& y)
{
	Point<float> pixelSize = calculatePixelSize();
	setStyle();
	collider_ = { pixelSize.x * x, pixelSize.y * y, pixelSize.x, pixelSize.y};
	collider_.drawRect();
}

void Cell::drawNeighbours()
{
	ofSetColor(ofColor::red);
	ofDrawBitmapString(count_, collider_.x, collider_.addYH());
}

void Cell::updateCell()
{
	if (markedForUpdate_) {
		isLive_          = isLive_ ? false : true;
		markedForUpdate_ = false;
	}
}

bool Cell::wasClickInside(int x, int y)
{
	return collider_.checkBounds(static_cast<float>(x),static_cast<float>(y));
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
		static_cast <float> (ofGetWidth()) / GRID_SIZE,
		static_cast <float> (ofGetHeight()) / GRID_SIZE
	};

	return output;
}
