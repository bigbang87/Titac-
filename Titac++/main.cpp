#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameDelegate.h"
#include "MainMenuScene.h"

#include "UIImage.h"
#include "DummyClass.h"
#include "Canvas.h"

int main()
{
	std::string windowName = "TEST";
	sf::RenderWindow window(sf::VideoMode(800, 600), windowName, sf::Style::Default);
	std::cout << "Program initialized successfully\n";

	GameDelegate gameDelegate(window);
	std::unique_ptr<Scene> currentScenePtr = nullptr;
	currentScenePtr = std::make_unique<MainMenuScene>(window, gameDelegate);

	while (window.isOpen())
	{ 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			currentScenePtr->processEvents(event);
		}
		window.clear(sf::Color(241, 244, 66, 255));
		currentScenePtr->draw();
		window.display();
	}

	return 0;
}