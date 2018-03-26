#pragma once

#include "Canvas.h"
#include "Actor.h"

class Scene
{
protected:
	virtual void onInitialize() {};
	std::unique_ptr<Canvas> m_canvas;

public:
	Scene(sf::RenderWindow& window, GameDelegate& gameDelegate);
	virtual ~Scene() {};
	void updateActors();
	void draw();
	void processEvents(const sf::Event& e);

private:
	std::vector<std::unique_ptr<Actor>> actors;

protected:
	sf::RenderWindow& m_window;
	GameDelegate& m_gameDelegate;
};