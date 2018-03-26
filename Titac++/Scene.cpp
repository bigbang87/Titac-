#include "Scene.h"

Scene::Scene(sf::RenderWindow& window, GameDelegate& gameDelegate) : m_window(window), m_gameDelegate(gameDelegate)
{
	m_canvas = std::make_unique<Canvas>(window, gameDelegate);
}

void Scene::updateActors()
{
	for (auto& actor : actors)
	{

	}
}

void Scene::draw()
{
	m_canvas->drawElements();
}

void Scene::processEvents(const sf::Event& e)
{
	m_canvas->canvasEvent(e);
}
