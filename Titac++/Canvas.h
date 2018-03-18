#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UIElement.h"
#include "UIPanel.h"
#include "SFML/Window/Event.hpp"

class Canvas
{
private:
	std::unique_ptr<UIElement> m_root;
	sf::RenderWindow& m_renderWindow;
	std::vector<std::unique_ptr<UIElement>> elements;
	static Rect m_windowRect;

public:
	Canvas() = delete;
	Canvas(sf::RenderWindow& renderWindow);
	void removeUIElement(std::unique_ptr<UIElement> uiElementPtr);
	void addElement(std::unique_ptr<UIElement> uiElementPtr);
	void canvasEvent(const sf::Event& e);
	void drawElements();
	void updateWindowRect();
	static const Rect getWindowRect();
	static const sf::Vector2i getWindowPosition();
	static const sf::Vector2i getReleativeMousePosition();
};