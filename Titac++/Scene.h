#pragma once

#include "Canvas.h"
#include "Actor.h"

class Scene
{
private:
	std::unique_ptr<Canvas> canvas;
	std::vector<std::unique_ptr<Actor>> actors;

public:
	Scene(sf::RenderWindow& window, GameDelegate& gameDelegate);
};