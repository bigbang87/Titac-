#pragma once

#include <string>
#include <memory>

namespace sf { class Font; }

class ResourceFont
{
public:
	ResourceFont() = delete;
	ResourceFont(const std::string& path);
	const sf::Font& getFont();

private:
	std::unique_ptr<sf::Font> m_fontPtr;
};