#pragma once
#include <string>
#include <memory>

namespace sf { class Texture; }

class ResourceImage
{
public:
	ResourceImage() = delete;
	ResourceImage(const std::string& path);
	const sf::Texture& getTexture();

private:
	std::unique_ptr<sf::Texture> m_texturePtr;
};