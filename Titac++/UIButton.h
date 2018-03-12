#pragma once

#include "UIImage.h"
#include <functional>
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
	std::function<void()> callback;

	void onDraw(sf::RenderWindow &window, int offsetX, int offsetY) override;
	void onEvent(sf::Event &e) override;
	void callListeners();

public:
	UIButton(Rect rect, const sf::RenderWindow& window);
	UIButton(Rect rect, const sf::RenderWindow& window, const std::string& defImage,
		const std::string& hoverImage, const std::string& clickImage);

	template<typename T>
	void addListener(T value);
	~UIButton();
};

template<typename T>
inline void UIButton::addListener(T value)
{
	callback = value;
}
