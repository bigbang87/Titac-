#include "UIElement.h"

UIElemenmt::UIElemenmt()
{
}

void UIElemenmt::loadImage(std::string name)
{
	sf::Texture texture;
	texture.loadFromFile(name);
}

void UIElemenmt::setSize(unsigned int height, unsigned int with)
{
}

void UIElemenmt::setPosition(unsigned int x, unsigned int y)
{
}

const Rect & UIElemenmt::getRect()
{
	// TODO: insert return statement here
}

void UIElemenmt::draw()
{
}
