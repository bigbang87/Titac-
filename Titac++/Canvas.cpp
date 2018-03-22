#include "Canvas.h"
#include <iostream>

Canvas::Canvas(sf::RenderWindow& renderWindow, GameDelegate& gameDelegate) : m_renderWindow(renderWindow), m_gameDelegate(gameDelegate)
{
	sf::IntRect windowRect(0, 0, renderWindow.getSize().x, renderWindow.getSize().y);
	m_root = std::make_unique<UIPanel>(std::move(windowRect));

	//std::unique_ptr<UIButton> btnPtr = std::make_unique<UIButton>(sf::IntRect(100, 200, 256, 128), "standard.jpg", "hover.jpg", "pressed.jpg");
	//btnPtr->addPressedListener([&gameDelegate]() {gameDelegate.setResolution(sf::Vector2u(700, 700)); });
	//addElement(std::move(btnPtr));
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
		m_renderWindow.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
		updateResolution(sf::Vector2u(e.size.width, e.size.height));
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

void Canvas::updateResolution(sf::Vector2u newRes)
{
	sf::Vector2u oldRes = m_gameDelegate.getOriginalResolution();
	float xScaleRatio = (float)newRes.x / (float)oldRes.x;
	float yScaleRatio = (float)newRes.y / (float)oldRes.y;
	sf::Vector2f newScale(xScaleRatio, yScaleRatio);
	for (auto const& element : elements)
		element->setLocalScale(newScale);
}