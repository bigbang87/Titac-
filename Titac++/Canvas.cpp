#include "Canvas.h"
#include <iostream>

sf::IntRect Canvas::m_windowRect;

Canvas::Canvas(sf::RenderWindow& renderWindow, GameDelegate& gameDelegate) : m_renderWindow(renderWindow), m_gameDelegate(gameDelegate)
{
	sf::Vector2i pos = renderWindow.getPosition();
	sf::Vector2u size = renderWindow.getSize();
	sf::IntRect windowRect = sf::IntRect(pos.x, pos.y, size.x, size.y);
	m_root = std::make_unique<UIPanel>(std::move(windowRect));
	m_oldWindowRect = std::move(windowRect);

	std::unique_ptr<UIButton> btnPtr = std::make_unique<UIButton>(sf::IntRect(100, 200, 256, 128), "standard.jpg", "hover.jpg", "pressed.jpg");
	btnPtr->addPressedListener([&gameDelegate]() {gameDelegate.setResoluationFromCursor(); });
	addElement(std::move(btnPtr));
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
	case sf::Event::Resized:
		updateWindowRect();
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
	m_windowRect = std::move(sf::IntRect(pos.x, pos.y, size.x, size.y));
	//std::cout << m_renderWindow.getSize().x << ", " << m_renderWindow.getSize().y << "\n";
	//std::cout << m_oldWindowRect.width << ", " << m_oldWindowRect.height << "\n";
	float xSizeRatio, ySizeRatio;
	int newXPos, newYPos;
	unsigned int newXSize, newYSize;
	sf::IntRect elementRect;
	for (auto const& element : elements)
	{
		xSizeRatio = (float)m_renderWindow.getSize().x / (float)m_oldWindowRect.width;
		ySizeRatio = (float)m_renderWindow.getSize().y / (float)m_oldWindowRect.height;
		elementRect = element->getRect();
		newXPos = (int)(elementRect.left * xSizeRatio);
		newYPos = (int)(elementRect.top * ySizeRatio);
		newXSize = (unsigned int)(elementRect.width * xSizeRatio);
		newYSize = (unsigned int)(elementRect.height * ySizeRatio);
		element->setPosition(newXPos, newYPos);
		element->setSize(newXSize, newYSize);
	}
	m_oldWindowRect = m_windowRect;
}

const sf::IntRect Canvas::getWindowRect()
{
	return m_windowRect;
}

const sf::Vector2i Canvas::getWindowPosition()
{
	return sf::Vector2i(m_windowRect.left, m_windowRect.top);
}

const sf::Vector2i Canvas::getReleativeMousePosition()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2i windowPos = Canvas::getWindowPosition();
	sf::Vector2i relativeMousePos = sf::Mouse::getPosition() - Canvas::getWindowPosition();
	return relativeMousePos;
}
