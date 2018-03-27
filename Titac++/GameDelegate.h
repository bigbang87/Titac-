#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class Scene;

class GameDelegate
{
private:
	sf::Vector2u m_originalResolution;
	sf::Vector2u m_resolution;
	sf::RenderWindow& m_window;
	std::unique_ptr<Scene> m_currentScene;

public:
	GameDelegate() = delete;
	GameDelegate(sf::RenderWindow& renderWindow);
	//display
	void setResolution(sf::Vector2u& resolution);
	const sf::Vector2u getResolution();
	const sf::Vector2u getOriginalResolution();
	const sf::Vector2u getFixedRatioResolution(const unsigned int x, const unsigned int y);
	//scene management
	void loadScene(std::unique_ptr<Scene> scene);
	Scene* getCurrentScene();
};