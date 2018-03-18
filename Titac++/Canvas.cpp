#include "Canvas.h"
#include <iostream>

Rect Canvas::m_windowRect;

Canvas::Canvas(sf::RenderWindow& renderWindow) : m_renderWindow(renderWindow)
{
	sf::Vector2i pos = renderWindow.getPosition();
	sf::Vector2u size = renderWindow.getSize();
	Rect windowRect = Rect(pos.x, pos.y, size.x, size.y);
	m_root = std::make_unique<UIPanel>(std::move(windowRect));
}

void Canvas::removeUIElement(std::unique_ptr<UIElement> uiElementPtr)
{
}

void Canvas::addElement(std::unique_ptr<UIElement> uiElementPtr)
{
	if (uiElementPtr->getParent() == nullptr)
		uiElementPtr->setParent(m_root.get());
	elements.push_back(std::move(uiElementPtr));
}

void Canvas::canvasEvent(const sf::Event& e)
{
	bool canProcess = false;
	switch (e.type)
	{
	case sf::Event::MouseMoved:
		canProcess = true;
		break;
	case sf::Event::MouseButtonPressed:
		canProcess = true;
		break;
	case sf::Event::MouseButtonReleased:
		canProcess = true;
		break;
	}
	if (canProcess)
		for (auto const& element : elements)
			element->event(e);
}

void Canvas::drawElements()
{
	for (auto const& element : elements)
		element->draw(m_renderWindow, 0, 0);
}

void Canvas::updateWindowRect()
{
	sf::Vector2i pos = m_renderWindow.getPosition();
	sf::Vector2u size = m_renderWindow.getSize();
	m_windowRect = std::move(Rect(pos.x, pos.y, size.x, size.y));
}

const Rect Canvas::getWindowRect()
{
	return m_windowRect;
}

const sf::Vector2i Canvas::getWindowPosition()
{
	return sf::Vector2i(m_windowRect.x, m_windowRect.y);
}

const sf::Vector2i Canvas::getReleativeMousePosition()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2i windowPos = Canvas::getWindowPosition();
	sf::Vector2i relativeMousePos = sf::Mouse::getPosition() - Canvas::getWindowPosition();
	std::cout << relativeMousePos.x << ", " << relativeMousePos.y << "\n";
	return relativeMousePos;
}
