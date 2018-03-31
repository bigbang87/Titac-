#include "Canvas.h"
#include <iostream>

Canvas::Canvas(sf::RenderWindow& renderWindow, GameDelegate& gameDelegate) : m_renderWindow(renderWindow), m_gameDelegate(gameDelegate)
{
	sf::IntRect windowRect(0, 0, renderWindow.getSize().x, renderWindow.getSize().y);
	m_root = std::make_unique<UIPanel>(std::move(windowRect));
}

void Canvas::removeUIElement(std::unique_ptr<UIElement> uiElementPtr)
{
}

void Canvas::addElement(std::unique_ptr<UIElement> uiElementPtr)
{
	if (uiElementPtr->getParent() == nullptr)
		uiElementPtr->setParent(m_root.get());
	sf::Vector2u originalRes = m_gameDelegate.getOriginalResolution();
	sf::Vector2u currentRes = m_gameDelegate.getResolution();
	float newScaleX = (float)currentRes.x / (float)originalRes.x;
	float newScaleY = (float)currentRes.y / (float)originalRes.y;
	sf::Vector2f scale = sf::Vector2f(newScaleX, newScaleY);
	uiElementPtr->setLocalScale(scale);
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
		sf::Vector2u fixedRes = m_gameDelegate.getFixedRatioResolution(e.size.width, e.size.height);
		updateResolution(fixedRes);
		canProcess = true;
		break;
	}

	int initialElementsSize = elements.size();
	if (canProcess)
		for (auto const& element : elements)
		{
			//ask some real programmer how to dela with collection size changed during the execution
			if (elements.size() == 0 || elements.size() > initialElementsSize)
				return;
			element->event(e);
		}
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
	sf::Vector2f newScale = sf::Vector2f(xScaleRatio, yScaleRatio);
	for (auto const& element : elements)
		element->setLocalScale(newScale);
	m_gameDelegate.setResolution(newRes);
}