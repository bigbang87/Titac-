#include "ResourceFont.h"
#include <SFML/Graphics.hpp>

ResourceFont::ResourceFont(const std::string& path) : m_fontPtr(std::make_unique<sf::Font>())
{
	const std::string resourcePath = "resources/fonts/" + path;
	m_fontPtr->loadFromFile(resourcePath);
}

const sf::Font& ResourceFont::getFont()
{
	return *m_fontPtr;
}
