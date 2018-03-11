#pragma once

#include "UIImage.h"
#include "SFML/Graphics/Rect.hpp"

class UIButton : public UIElement
{
private:
	const UIElement* m_parent = nullptr;
	std::unique_ptr<UIImage> m_defaultImage;
	std::unique_ptr<UIImage> m_hoverImage;
	std::unique_ptr<UIImage> m_clickImage;
	sf::IntRect m_sfRect;
	const sf::RenderWindow& m_window;

	void onDraw(sf::RenderWindow &window, int offsetX, int offsetY) override;
	void onEvent(sf::Event &e) override;

public:
	UIButton(Rect rect, const sf::RenderWindow& window);
	UIButton(Rect rect, const sf::RenderWindow& window, const std::string& defImage,
		const std::string& hoverImage, const std::string& clickImage);
	~UIButton();
};