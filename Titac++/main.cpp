#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameDelegate.h"
#include "Scenes.h"

#include "UIImage.h"
#include "DummyClass.h"
#include "Canvas.h"

int main()
{
	std::string windowName = "TEST";
	sf::RenderWindow window(sf::VideoMode(512, 512), windowName, sf::Style::Default);
	std::cout << "Program initialized successfully\n";

	GameDelegate gameDelegate(window);
	gameDelegate.loadScene(std::make_unique<MainMenuScene>(window, gameDelegate));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			gameDelegate.getCurrentScene()->processEvents(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(241, 244, 66, 255));
		gameDelegate.getCurrentScene()->draw();
		window.display();
	}

	return 0;
}