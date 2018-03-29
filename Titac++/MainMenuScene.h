#pragma once

#include "Scene.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(sf::RenderWindow& windows, GameDelegate& gameDelegate) : Scene(windows, gameDelegate)
	{
	}
	
	void onInitialize() override
	{
		//title
		std::unique_ptr<UIText> textPtr = std::make_unique<UIText>(sf::IntRect(150, 0, 50, 50), "archive.otf");
		std::string testText = "Test Game";
		textPtr->setText(testText);
		textPtr->setColor(sf::Color(255, 92, 56));
		m_canvas->addElement(std::move(textPtr));

		std::unique_ptr<UIButton> startBtnPtr = std::make_unique<UIButton>(sf::IntRect(128, 150, 256, 88),
			"defaultStartButton.png", "hoverStartButton.png", "pressedStartButton.png");
		//DummyClass dummyClass;
		//btnPtr->addListener([&dummyClass]() {dummyClass.printMe(); });
		m_canvas->addElement(std::move(startBtnPtr));
		std::unique_ptr<UIButton> exitBtnPtr = std::make_unique<UIButton>(sf::IntRect(128, 270, 256, 88),
			"defaultExitButton.png", "hoverExitButton.png", "pressedExitButton.png");
		m_canvas->addElement(std::move(exitBtnPtr));
		std::cout << "MainMenuScene loaded\n";
	}
};