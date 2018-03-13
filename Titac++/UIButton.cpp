#include "UIButton.h"
#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>

#include <sstream>

UIButton::UIButton(Rect rect, const sf::RenderWindow& window) : UIElement(rect), m_window(window),
	m_sfRect(rect.x, rect.y, rect.width, rect.height),
	m_defaultImage(nullptr), m_hoverImage(nullptr), m_clickImage(nullptr)
{
}

UIButton::UIButton(Rect rect, const sf::RenderWindow& window,
	const std::string& defImage, const std::string& hoverImage, const std::string& clickImage) :
	UIElement(rect), m_window(window), m_sfRect(rect.x, rect.y, rect.width, rect.height)
{
	if (!defImage.empty())
		m_defaultImage = std::make_unique<UIImage>(Rect(0, 0, 256, 256), defImage);
	if (!hoverImage.empty())
		m_hoverImage = std::make_unique<UIImage>(Rect(0, 0, 256, 256), hoverImage);
	if (!clickImage.empty())
		m_clickImage = std::make_unique<UIImage>(Rect(0, 0, 256, 256), clickImage);
}

void UIButton::onDraw(sf::RenderWindow& window, int offsetX, int offsetY)
{
	if (m_defaultImage != nullptr)
		m_defaultImage->onDraw(window, offsetX, offsetY);
}

void UIButton::onEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		sf::Vector2i windowPos = m_window.getPosition();
		sf::Vector2i relativeMousePos = sf::Mouse::getPosition() - m_window.getPosition();
		if (m_sfRect.contains(relativeMousePos.x, relativeMousePos.y))
		{
			callListeners();
			/*
			std::ostringstream ss;
			ss << sf::Mouse::getPosition().x;
			ss << ", ";
			ss << sf::Mouse::getPosition().y;
			ss << "\n";
			std::string s(ss.str());
			printf(s.c_str());
			*/
		}
	}
}

void UIButton::addListener(std::function<void()> listener)
{
	callback = std::move(listener);
}

void UIButton::callListeners()
{
	//to do
	//event propagation
	//for (auto const& listener : listeners)
	//	listener();
	callback();
}

UIButton::~UIButton()
{
}
