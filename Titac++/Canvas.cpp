#include "Canvas.h"

Canvas::Canvas(sf::RenderWindow& renderWindow) : m_renderWindow(renderWindow)
{
}

void Canvas::removeUIElement(std::unique_ptr<UIElement> uiElementPtr)
{
}

void Canvas::addElement(std::unique_ptr<UIElement> uiElementPtr)
{
	elements.push_back(std::move(uiElementPtr));
}

void Canvas::canvasEvent(const sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::MouseMoved:
		for (auto const& element : elements)
			element->event(e);
		break;
	}
}

void Canvas::drawElements()
{
	for (auto const& element : elements)
		element->draw(m_renderWindow, 0, 0);
}
