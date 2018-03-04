#pragma once
struct Rect {
	unsigned int with;
	unsigned int height;
	int x;
	int y;

	Rect();
	Rect(unsigned int withValue, unsigned int heightValue, int xValue, int yValue) :
		with(withValue), height(heightValue), x(xValue), y(yValue)
	{
	}
};