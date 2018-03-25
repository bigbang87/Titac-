#pragma once

#include "UIElement.h"
#include "ResourceIncludes.h"

class UIText : public UIElement
{
private:
	class SFTextImpl;
	std::unique_ptr<SFTextImpl> pimpl;
public:
	UIText(sf::IntRect rect, const std::string& path);
	void setText(std::string& text);
	void onDraw(sf::RenderWindow& window, int offsetX, int offsetY) override;
	void setColor(const sf::Color& color);
};