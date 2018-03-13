#include <SFML/Graphics.hpp>
#include <string>

#include "UIImage.h"
#include "UIButton.h"
#include "DummyClass.h"
#include "Canvas.h"

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
	DummyClass dummyClass;

	Canvas canvas(window);
	std::unique_ptr<UIButton> btnPtr = std::make_unique<UIButton>(Rect(0, 0, 256, 256), window, "test.jpg", "", "");
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
		window.clear();
		canvas.drawElements();
		window.display();
	}

	return 0;
}