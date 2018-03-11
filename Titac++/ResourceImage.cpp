#include "ResourceImage.h"
#include <SFML/Graphics.hpp>

ResourceImage::ResourceImage(const std::string& path) : m_texturePtr(std::make_unique<sf::Texture>())
{
	const std::string resourcePath = "resources/images/" + path;
	m_texturePtr->loadFromFile(resourcePath);
}

const sf::Texture& ResourceImage::getTexture()
{
	return *m_texturePtr;
}
