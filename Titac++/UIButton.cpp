#include "UIButton.h"

UIButton::UIButton(Rect rect) : UIElement(rect), m_sfRect(rect.x, rect.y, rect.width, rect.height),
	m_defaultImage(nullptr), m_hoverImage(nullptr), m_clickImage(nullptr)
{
}

UIButton::UIButton(Rect rect, const std::string& defImage, const std::string& hoverImage, const std::string& clickImage) : 
	UIElement(rect), m_sfRect(rect.x, rect.y, rect.width, rect.height)
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

void UIButton::onEvent(sf::Event& e)
{
	while (window.pollEvent(r))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

UIButton::~UIButton()
{
}
