#include "UIText.h"
#include <SFML/Graphics.hpp>

class UIText::SFTextImpl
{
public:
	SFTextImpl(const std::string& path) : m_text(std::make_unique<sf::Text>())
	{
		m_resource = ResourceManager<ResourceFont>::get().loadResource(path);
		m_text->setFont(m_resource->getFont());
	}
	void draw(sf::RenderWindow& window, int offsetX, int offsetY)
	{
		window.draw(*m_text);
	}

	void setScale(float scaleX, float scaleY)
	{
		m_text->setScale(scaleX, scaleY);
	}

	void setText(std::string& text)
	{
		m_text->setString(text);
	}

	void setPosition(const sf::Vector2f& position)
	{
		m_text->setPosition(position);
	}

	void setColor(const sf::Color& color)
	{
		m_text->setFillColor(color);
	}


private:
	std::unique_ptr<sf::Text> m_text;
	std::shared_ptr<ResourceFont> m_resource;
};

UIText::UIText(sf::IntRect rect, const std::string& path)
	: UIElement(rect), pimpl(std::make_unique<SFTextImpl>(path))
{
	pimpl->setPosition(sf::Vector2f(rect.left, rect.top));
}

void UIText::setText(std::string& text)
{
	pimpl->setText(text);
}

void UIText::onDraw(sf::RenderWindow& window, int offsetX, int offsetY)
{
	pimpl->draw(window, offsetX, offsetY);
}

void UIText::setColor(const sf::Color& color)
{
	pimpl->setColor(color);
}
