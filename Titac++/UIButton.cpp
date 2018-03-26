#include "UIButton.h"
#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Canvas.h"

UIButton::UIButton(sf::IntRect rect) : UIElement(rect),
	m_defaultImage(nullptr), m_hoverImage(nullptr), m_pressImage(nullptr)
{
}

UIButton::UIButton(sf::IntRect rect, const std::string& defImage, const std::string& hoverImage,
	const std::string& pressImage) : UIElement(rect)
{
	if (!defImage.empty())
		m_defaultImage = std::make_unique<UIImage>(rect, defImage);
	if (!hoverImage.empty())
		m_hoverImage = std::make_unique<UIImage>(rect, hoverImage);
	if (!pressImage.empty())
		m_pressImage = std::make_unique<UIImage>(rect, pressImage);
}

void UIButton::onDraw(sf::RenderWindow& window, const int offsetX, const int offsetY)
{
	switch (m_state)
	{
	case States::hover:
		m_hoverImage->onDraw(window, offsetX, offsetY);
		break;
	case States::pressed:
		m_pressImage->onDraw(window, offsetX, offsetY);
		break;
	default:
		if (m_defaultImage != nullptr)
			m_defaultImage->onDraw(window, offsetX, offsetY);
	}
}

void UIButton::onScale(const sf::Vector2f scale)
{
	//std::cout << "UIButton Rect: " << m_rect.width << ", " << m_rect.height << "\n";
	if (m_defaultImage != nullptr)
		m_defaultImage->setLocalScale(scale);
	if (m_hoverImage != nullptr)
		m_hoverImage->setLocalScale(scale);
	if (m_pressImage != nullptr)
		m_pressImage->setLocalScale(scale);
}

bool UIButton::onEvent(const sf::Event& e)
{
	const sf::Vector2i mousePos = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);
	switch (e.type)
	{
	case sf::Event::MouseMoved:
		if (m_rect.contains(mousePos.x, mousePos.y)) {
			if (m_state != States::pressed)
				onHover();
		}
		else
			if (m_state == States::hover || m_state == States::pressed)
				m_state = States::standard;
		break;
	case sf::Event::MouseButtonPressed:
		if (e.mouseButton.button == sf::Mouse::Left && m_state == States::hover)
			onPressed();
		break;
	case sf::Event::MouseButtonReleased:
		if (e.mouseButton.button == sf::Mouse::Left && m_state == States::pressed)
		{
			onClick();
		}
		break;
	}
	return false;
}

void UIButton::addListener(std::function<void()> listener)
{
	m_callback = std::move(listener);
}

void UIButton::addPressedListener(std::function<void()> listener)
{
	m_pressCallBack = std::move(listener);
}

void UIButton::callListeners()
{
	//to do
	//event propagation
	//for (auto const& listener : listeners)
	//	listener();
	if (m_callback != NULL)
		m_callback();
}

bool UIButton::onHover()
{
	m_state = States::hover;
	//std::cout << "UIButton :" << m_rect.width << ", " << m_rect.height << "\n";
	return true;
}

bool UIButton::onPressed()
{
	m_state = States::pressed;
	if (m_pressCallBack != NULL)
	{
		m_pressCallBack();
	}
	return true;
}

void UIButton::onClick()
{
	m_state = States::hover;
	callListeners();
}
