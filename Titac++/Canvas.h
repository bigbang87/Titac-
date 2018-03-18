#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UIElement.h"
#include "UIPanel.h"
#include "SFML/Window/Event.hpp"
#include "UIButton.h"
#include "GameDelegate.h"

class Canvas
{
private:
	std::unique_ptr<UIElement> m_root;
	sf::RenderWindow& m_renderWindow;
	GameDelegate& m_gameDelegate;
	std::vector<std::unique_ptr<UIElement>> elements;
	static sf::IntRect m_windowRect;
	sf::IntRect m_oldWindowRect;

public:
	Canvas() = delete;
	Canvas(sf::RenderWindow& renderWindow, GameDelegate& gameDelegate);
	void removeUIElement(std::unique_ptr<UIElement> uiElementPtr);
	void addElement(std::unique_ptr<UIElement> uiElementPtr);
	void canvasEvent(const sf::Event& e);
	void drawElements();
	void updateWindowRect();
	static const sf::IntRect getWindowRect();
	static const sf::Vector2i getWindowPosition();
	static const sf::Vector2i getReleativeMousePosition();
};