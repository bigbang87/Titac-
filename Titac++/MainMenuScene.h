#pragma once

#include "Scene.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(sf::RenderWindow& windows, GameDelegate& gameDelegate) : Scene(windows, gameDelegate)
	{
		onInitialize();
	}
	
	void onInitialize() override
	{
		std::unique_ptr<UIButton> btnPtr = std::make_unique<UIButton>(sf::IntRect(100, 50, 256, 128), "standard.jpg", "hover.jpg", "pressed.jpg");
		//DummyClass dummyClass;
		//btnPtr->addListener([&dummyClass]() {dummyClass.printMe(); });
		m_canvas->addElement(std::move(btnPtr));
		std::unique_ptr<UIText> textPtr = std::make_unique<UIText>(sf::IntRect(10, 400, 50, 50), "arial.ttf");
		std::string testText = "TEST";
		textPtr->setText(testText);
		textPtr->setColor(sf::Color(244, 248, 255));
		m_canvas->addElement(std::move(textPtr));

		std::cout << "MainMenuScene loaded\n";
	}
};