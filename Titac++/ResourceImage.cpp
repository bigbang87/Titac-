#include "ResourceImage.h"
#include <SFML/Graphics.hpp>

ResourceImage::ResourceImage(const std::string& path) : m_texturePtr(std::make_unique<sf::Texture>())
{
	m_texturePtr->loadFromFile(path);
}

const sf::Texture& ResourceImage::getTexture()
{
	return *m_texturePtr;
}
