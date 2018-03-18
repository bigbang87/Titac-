#pragma once
struct Rects {
	int x;
	int y;
	unsigned int width;
	unsigned int height;

	Rects() : x(0), y(0), width(0), height(0)
	{
	}

	Rects(int xValue, int yValue, unsigned int withValue, unsigned int heightValue) :
		x(xValue), y(yValue), width(withValue), height(heightValue)
	{
	}
};