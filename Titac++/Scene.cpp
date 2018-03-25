#include "Scene.h"

Scene::Scene(sf::RenderWindow& window, GameDelegate& gameDelegate)
{
	canvas = std::make_unique<Canvas>(window, gameDelegate);
}
