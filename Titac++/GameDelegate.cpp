#include "GameDelegate.h"
#include <iostream>
#include "Scene.h"

GameDelegate::GameDelegate(sf::RenderWindow& renderWindow) : m_window(renderWindow)
{
	m_originalResolution = renderWindow.getSize();
	m_resolution = renderWindow.getSize();
	m_currentScene = nullptr;
}

void GameDelegate::setResolution(sf::Vector2u& resolution)
{
	if (resolution == m_window.getSize())
		return;
	m_window.setView(sf::View(sf::FloatRect(0, 0, resolution.x, resolution.y)));
	m_resolution = resolution;
	m_window.setSize(resolution);
	std::cout << "GameDelegate: resolution set to " << resolution.x << " x " << resolution.y << "\n";
}

const sf::Vector2u GameDelegate::getResolution()
{
	return m_resolution;
}

const sf::Vector2u GameDelegate::getOriginalResolution()
{
	return m_originalResolution;
}

const sf::Vector2u GameDelegate::getFixedRatioResolution(const unsigned int x, const unsigned int y)
{
	float newRatio = 0;
	float widthRatio = 0;
	sf::Vector2u res;
	if (m_resolution.y != y)
	{
		newRatio = (float)m_originalResolution.y / y;
		widthRatio = (float)m_originalResolution.x / newRatio;
		res = sf::Vector2u(widthRatio, y);
		return res;
	}
	if (m_resolution.x != x)
	{
		newRatio = (float)m_originalResolution.x / x;
		widthRatio = (float)m_originalResolution.y / newRatio;
		res = sf::Vector2u(x, widthRatio);
		return res;
	}
	return sf::Vector2u(x, y);
}

/*
void GameDelegate::loadScene(std::unique_ptr<Scene> scene)
{
	Scene* scenePtr = scene.get();
	m_deferredTasks.addTask([this, scenePtr]() {deferredLoadGame(scenePtr); });
}
*/

/*
void GameDelegate::loadScene(std::unique_ptr<Scene> scene)
{
	m_currentScene.reset();
	m_currentScene = std::move(scene);
	m_currentScene->onInitialize();
}
*/

void GameDelegate::loadScene(Scene* scene)
{
	m_deferredTasks.addTask([this, scene]() {deferredLoadGame(scene); });
}

void GameDelegate::deferredLoadGame(Scene* scene)
{
	m_currentScene.reset();
	m_currentScene = std::move(std::unique_ptr<Scene>(scene));
	m_currentScene->onInitialize();
}

Scene* GameDelegate::getCurrentScene()
{
	return m_currentScene.get();
}