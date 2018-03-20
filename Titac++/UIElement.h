#pragma once
#include <string>
#include <memory>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

class Scene;
namespace sf { class RenderWindow; class Event; }

class UIElement {
protected:
	const UIElement* m_parent = nullptr;
	std::vector<std::unique_ptr<UIElement>> m_children;
	sf::IntRect m_rect;

public:
	UIElement(const sf::IntRect& rect);
	void setSize(unsigned int width, unsigned int height);
	void setPosition(int x, int y);
	const sf::IntRect& getRect();
	void addChild(std::unique_ptr<UIElement> child);
	void draw(sf::RenderWindow &window, int offsetX, int offsetY);
	bool event(const sf::Event &e);
	void setParent(const UIElement* parent);
	const UIElement* getParent();
	void scale(float scaleFactorX, float scaleFactorY);
	virtual ~UIElement();

private:
	virtual void onDraw(sf::RenderWindow &window, int offsetX, int offsetY) {};
	virtual bool onEvent(const sf::Event &e) { return false; };
	virtual void onScale(float scaleX, float scaleY) {};
	friend class Scene;
};