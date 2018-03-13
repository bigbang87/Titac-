#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UIElement.h"
#include "SFML/Window/Event.hpp"

class Canvas
{
private:
	std::unique_ptr<UIElement> m_root;
	sf::RenderWindow& m_renderWindow;
	std::vector<std::unique_ptr<UIElement>> elements;
public:
	Canvas() = delete;
	Canvas(sf::RenderWindow& renderWindow);
	void removeUIElement(std::unique_ptr<UIElement> uiElementPtr);
	void addElement(std::unique_ptr<UIElement> uiElementPtr);
	void canvasEvent(const sf::Event& e);
	void drawElements();
};