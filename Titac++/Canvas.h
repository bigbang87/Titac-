#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UIElement.h"

class Canvas
{
private:
	std::unique_ptr<UIElement> m_root;
	sf::RenderWindow &m_renderWindow;

public:
	Canvas() = delete;
	Canvas(sf::RenderWindow &renderWindow);
	void renderScene();
	void removeUIElement();
};