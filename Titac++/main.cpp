#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameDelegate.h"

#include "UIImage.h"
#include "DummyClass.h"
#include "Canvas.h"

int main()
{
	std::string windowName = "TEST";
	sf::RenderWindow window(sf::VideoMode(500, 500), windowName, sf::Style::Default);
	GameDelegate gameDelegate(window);
	DummyClass dummyClass;

	Canvas canvas(window, gameDelegate);
	std::unique_ptr<UIButton> btnPtr = std::make_unique<UIButton>(sf::IntRect(100, 50, 256, 128), "standard.jpg", "hover.jpg", "pressed.jpg");
	btnPtr->addListener([&dummyClass]() {dummyClass.printMe(); });
	canvas.addElement(std::move(btnPtr));

	while (window.isOpen())
	{ 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			canvas.canvasEvent(event);
		}
		window.clear(sf::Color(241, 244, 66, 255));
		canvas.drawElements();
		window.display();
	}

	return 0;
}