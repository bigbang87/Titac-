#pragma once
#include "Rect.h"
#include <string>
#include <memory>
#include <vector>

class Scene;
namespace sf { class RenderWindow; class Event; }

class UIElement {
protected:
	const UIElement* m_parent = nullptr;
	std::vector<std::unique_ptr<UIElement>> m_children;
	Rect m_rect;

public:
	UIElement(const Rect& rect);
	void loadImage(const std::string& name);
	void setSize(unsigned int width, unsigned int height);
	void setPosition(unsigned int x, unsigned int y);
	void addChild(std::unique_ptr<UIElement> child);
	const Rect& getRect();
	void draw(sf::RenderWindow &window, int offsetX, int offsetY);
	void event(const sf::Event &e);

private:
	virtual void onDraw(sf::RenderWindow &window, int offsetX, int offsetY) {};
	virtual void onEvent(const sf::Event &e) {};
	virtual void setScale(float scaleX, float scaleY) {};
	friend class Scene;
};