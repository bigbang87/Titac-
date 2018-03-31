#pragma once

#include "Scene.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(sf::RenderWindow& windows, GameDelegate& gameDelegate);
	void onInitialize() override;
};