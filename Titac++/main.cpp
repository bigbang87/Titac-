#include <SFML/Graphics.hpp>
#include <string>

#include "UIImage.h"
#include "UIButton.h"

int main()
{
	std::string windowName = "TEST";
	sf::RenderWindow window(sf::VideoMode(500, 500), windowName);

	/*
	UIImage test(Rect(0, 0, 256, 256), "test.jpg");
	test.addChild(std::make_unique<UIImage>(Rect(50, 50, 150, 150), "test.jpg"));
	test.addChild(std::make_unique<UIImage>(Rect(100, 100, 100, 100), "test.jpg"));
	test.addChild(std::make_unique<UIImage>(Rect(150, 150, 50, 50), "test.jpg"));
	*/
	UIButton test(Rect(0, 0, 256, 256), window, "test.jpg", "", "");


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			test.event(event);
		}
		window.clear();
		test.draw(window, 0, 0);
		window.display();
	}

	return 0;
}