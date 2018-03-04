#pragma once
#include "Rect.h"
#include <SFML/Graphics.hpp>
#include <string>

class UIElemenmt {
private:
	Rect m_rect;
	sf::Sprite sprite;
public:
	UIElemenmt();
	void loadImage(std::string name);
	void setSize(unsigned int height, unsigned int with);
	void setPosition(unsigned int x, unsigned int y);
	const Rect& getRect();
	void draw();
};