#pragma once

#include "UIElement.h"
#include "ResourceIncludes.h"

class UIImage : public UIElement
{
private:
	const UIElement* m_parent = nullptr;
	class SFGraphicsImpl;
	std::unique_ptr<SFGraphicsImpl> pimpl;

public:
	UIImage(sf::IntRect rect, const std::string& path);
	void onDraw(sf::RenderWindow& window, const int offsetX, const int offsetY) override;
	void setRect(const sf::IntRect newRect) override;
	void setSprite(const std::string& path);
};