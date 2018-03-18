#pragma once

#include "UIImage.h"
#include <functional>
#include "SFML/Graphics/Rect.hpp"

class UIButton : public UIElement
{
public:
	enum class States
	{
		standard,
		hover,
		pressed
	};

private:
	const UIElement* m_parent = nullptr;
	std::unique_ptr<UIImage> m_defaultImage;
	std::unique_ptr<UIImage> m_hoverImage;
	std::unique_ptr<UIImage> m_pressImage;
	std::function<void()> m_callback;
	std::function<void()> m_pressCallBack;
	States m_state;

private:
	void onDraw(sf::RenderWindow &window, int offsetX, int offsetY) override;
	bool onEvent(const sf::Event &e) override;
	void callListeners();
	void onClick();

public:
	UIButton(sf::IntRect rect);
	UIButton(sf::IntRect rect, const std::string& defImage,
		const std::string& hoverImage, const std::string& pressImage);
	void addListener(std::function<void()> listener);
	void addPressedListener(std::function<void()> listener);
	bool onHover();
	bool onPressed();
};