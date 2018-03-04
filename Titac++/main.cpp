#include <SFML/Graphics.hpp>
#include <string>
#include "UIElement.h"

int main()
{
	std::string s = "TEST";
	sf::RenderWindow window(sf::VideoMode(200, 200), s);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		//debug image - remove UIElement.h later
		//test
		//
		window.display();
	}

	return 0;
}