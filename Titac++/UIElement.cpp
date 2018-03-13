#include "UIElement.h"
#include <SFML/Graphics.hpp>

UIElement::UIElement(const Rect& rect) : m_rect(rect)
{
}

void UIElement::loadImage(const std::string& name)
{
}

void UIElement::setSize(unsigned int width, unsigned int height)
{
	m_rect = Rect(width, height, m_rect.x, m_rect.y);
}

void UIElement::setPosition(unsigned int x, unsigned int y)
{
	m_rect = Rect(m_rect.width, m_rect.height, x, y);
}

void UIElement::addChild(std::unique_ptr<UIElement> child)
{
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

const Rect & UIElement::getRect()
{
	return m_rect;
}

void UIElement::draw(sf::RenderWindow &window, int offsetX, int offsetY)
{
	onDraw(window, offsetX, offsetY);
	for(auto& child : m_children)
		child->draw(window, offsetX + m_rect.x, offsetY + m_rect.y);
}

void UIElement::event(const sf::Event& e)
{
	onEvent(e);
}
