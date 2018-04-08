#pragma once

#include "Scene.h"
#include "GameMap.h"

class GameScene : public Scene
{
public:
	GameScene(sf::RenderWindow& windows, GameDelegate& gameDelegate);
	void onInitialize() override;
private:
	Actor* m_GameMapPtr;
};