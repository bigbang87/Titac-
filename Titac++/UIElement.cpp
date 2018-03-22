#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include "Canvas.h"

UIElement::UIElement(const sf::IntRect& rect) : m_rect(rect), m_originalRect(rect)
{
}

void UIElement::setSize(unsigned int width, unsigned int height)
{
	m_rect = sf::IntRect(m_rect.left, m_rect.top, width, height);
}

void UIElement::setPosition(int x, int y)
{
	m_rect = sf::IntRect(x, y, m_rect.width, m_rect.height);
}

void UIElement::addChild(std::unique_ptr<UIElement> child)
{
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

const sf::IntRect& UIElement::getRect()
{
	return m_rect;
}

void UIElement::draw(sf::RenderWindow &window, int offsetX, int offsetY)
{
	onDraw(window, offsetX, offsetY);
	for(auto& child : m_children)
		child->draw(window, offsetX + m_rect.left, offsetY + m_rect.top);
}

bool UIElement::event(const sf::Event& e)
{
	return onEvent(e);
}

void UIElement::setParent(const UIElement* parent)
{
	m_parent = std::move(parent);
}

const UIElement* UIElement::getParent()
{
	return nullptr;
}

const sf::Vector2f UIElement::getLocalScale()
{
	return localScale;
}

void UIElement::setLocalScale(const sf::Vector2f scale)
{
	if (scale == localScale)
		return;
	localScale = scale;
	int newXPos, newYPos;
	unsigned int newXSize, newYSize;
	newXPos = (int)(m_originalRect.left * scale.x);
	newYPos = (int)(m_originalRect.top * scale.y);
	newXSize = (unsigned int)(m_originalRect.width * scale.x);
	newYSize = (unsigned int)(m_originalRect.height * scale.y);
	m_rect = sf::IntRect(newXPos, newYPos, newXSize, newYSize);
	onScale(scale);
	for (auto& child : m_children)
		child->setLocalScale(scale);
}

UIElement::~UIElement()
{
}
