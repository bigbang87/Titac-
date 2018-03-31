#pragma once

#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene(sf::RenderWindow& windows, GameDelegate& gameDelegate);
	void onInitialize() override;
};