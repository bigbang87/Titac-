#include "UIImage.h"
#include <SFML/Graphics.hpp>

class UIImage::SFGraphicsImpl
{
public:
	SFGraphicsImpl(const std::string& path) : m_sprite(std::make_unique<sf::Sprite>())
	{
		m_resource = ResourceManager<ResourceImage>::get().loadResource(path);
		m_sprite->setTexture(m_resource->getTexture());
	}
	void draw(sf::RenderWindow& window, int offsetX, int offsetY)
	{
		m_sprite->setPosition(offsetX, offsetY);
		window.draw(*m_sprite);
	}

	void setSize(int x, int y)
	{
		sf::Vector2u size = m_resource->getTexture().getSize();
		float newX = (float)x / size.x;
		float newY = (float)y / size.y;
		m_sprite->setScale(newX, newY);
	}

	void setScale(float scaleX, float scaleY)
	{
		m_sprite->setScale(scaleX, scaleY);
	}

	sf::Vector2u getSize()
	{
		return m_resource->getTexture().getSize();;
	}

private:
	std::unique_ptr<sf::Sprite> m_sprite;
	std::shared_ptr<ResourceImage> m_resource;
};

UIImage::UIImage(Rect rect, const std::string& path)
	: UIElement(rect), pimpl(std::make_unique<SFGraphicsImpl>(path))
{
	sf::Vector2u originalSize = pimpl->getSize();
	sf::Vector2u enteredSize(m_rect.width, m_rect.height);
	if (originalSize != enteredSize)
		pimpl->setSize(m_rect.width, m_rect.height);
}

void UIImage::onDraw(sf::RenderWindow& window, int offsetX, int offsetY)
{
	pimpl->draw(window, offsetX + m_rect.x, offsetY + m_rect.y);
}

void UIImage::setScale(float scaleX, float scaleY)
{
	pimpl->setScale(scaleX, scaleY);
}

UIImage::~UIImage()
{
}
