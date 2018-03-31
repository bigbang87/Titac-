#pragma once

#include "Scene.h"

class OptionsScene : public Scene
{
public:
	OptionsScene(sf::RenderWindow& windows, GameDelegate& gameDelegate);
	void onInitialize() override;
};