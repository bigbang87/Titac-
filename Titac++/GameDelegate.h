#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "DeferredTasks.h"

class Scene;

class GameDelegate
{
public:
	GameDelegate() = delete;
	GameDelegate(sf::RenderWindow& renderWindow);
	//display
	void setResolution(sf::Vector2u& resolution);
	const sf::Vector2u getResolution();
	const sf::Vector2u getOriginalResolution();
	const sf::Vector2u getFixedRatioResolution(const unsigned int x, const unsigned int y);
	//scene management
	void loadScene(Scene* scene);
	Scene* getCurrentScene();

private:
	//scene management
	void deferredLoadGame(Scene* scene);

public:
	DeferredTasks m_deferredTasks;

private:
	sf::Vector2u m_originalResolution;
	sf::Vector2u m_resolution;
	sf::RenderWindow& m_window;
	std::unique_ptr<Scene> m_currentScene;
};