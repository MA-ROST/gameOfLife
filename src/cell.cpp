﻿#include "cell.h"

int Cell::gridSize_{ 30 };

void Cell::setupPixel(const int& x, const int& y)
{
	const Point<float> pixelSize = calculatePixelSize();
	setStyle();
	collider_ = { pixelSize.x * x, pixelSize.y * y, pixelSize.x, pixelSize.y};
	collider_.drawRect();
}

void Cell::updateCell()
{
	if (markedForUpdate_) {
		isLive_          = isLive_ ? false : true;
		markedForUpdate_ = false;
	}
}

bool Cell::wasClickInside(const int x, const int y)
{
	return collider_.checkBounds(static_cast<float>(x),static_cast<float>(y));
}

void Cell::setStyle() const
{
	ofFill();
	if (isLive_) ofSetColor (active); 
	else {
		ofNoFill();
		ofSetColor (inactive);
	}
}

Point<float> Cell::calculatePixelSize()
{
	const Point <float> output{
		static_cast <float> (ofGetWidth()) / gridSize_,
		static_cast <float> (ofGetHeight()) / gridSize_
	};

	return output;
}
