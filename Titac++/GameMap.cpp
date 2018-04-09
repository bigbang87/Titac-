#include "GameMap.h"
#include "Scene.h"
#include <iostream>

GameMap::GameMap(const unsigned int sizeX, const unsigned int sizeY, Scene* scene) : m_scenePtr(scene)
{
	m_grid = std::make_unique<GenericGrid<int>>(sizeX, sizeY);

	/*for (GenericGrid<int>::Iterator i = m_grid->begin(); i != m_grid->end(); i++)
		std::cout << *i << " ";*/

	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x)
		{
			makeTile(x, y);
			m_grid->at(x, y) = 0;
		}
	}

	std::cout << "GameMap created with size of " << sizeX << " x " << sizeY << "\n";
}

void GameMap::makeTile(unsigned int x, unsigned int y)
{
	//calculating positions
	unsigned int tileSize = 64;
	int topMargin = 100;
	int spacing = 15;
	sf::Vector2u res = m_scenePtr->getGameDelegate().getResolution();
	std::size_t sizeX = m_grid->getSizeX();
	int tableSize = (int)((sizeX * tileSize) + (sizeX * spacing));
	int centringOffset = (int)((res.x - tableSize) * 0.5f) + (int)(spacing * 0.5f);
	int posX = (x * tileSize) + (x * spacing) + centringOffset;
	int posY = (y * tileSize) + (y * spacing) + topMargin;
	//adding button
	std::unique_ptr<UIButton> btnPtr = std::make_unique<UIButton>(sf::IntRect(posX, posY, tileSize, tileSize),
		"defaultMapTile.png", "hoverMapTile.png", "pressedMapTile.png");
	btnPtr->addListener([this, x, y]() {this->onClick(x, y); });
	m_scenePtr->getCanvas()->addElement(std::move(btnPtr));
	//adding images
	std::unique_ptr<UIImage> imagePtr = std::make_unique<UIImage>(sf::IntRect(posX, posY, tileSize, tileSize), "emptyFigure.png");
	m_images.push_back(imagePtr.get());
	m_scenePtr->getCanvas()->addElement(std::move(imagePtr));
}

void GameMap::onClick(unsigned int x, unsigned int y)
{
	int& getValue = m_grid->at(x, y);
	++getValue;
	getValue = (getValue == m_figuresMap.size()) ? 0 : getValue;
	const int imgPos = m_grid->getIdx(x, y);
	UIImage* imgPtr = m_images.at(imgPos);
	std::string path = m_figuresMap.at(getValue);
	imgPtr->setSprite(path);
	std::cout << "Clicked tile: [" << x << "][" << y << "] = " << m_grid->at(x, y) << "\n";
}