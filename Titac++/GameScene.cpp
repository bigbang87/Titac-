#include "Scenes.h"

GameScene::GameScene(sf::RenderWindow& windows, GameDelegate& gameDelegate) : Scene(windows, gameDelegate)
{
}

void GameScene::onInitialize()
{
	//title
	std::unique_ptr<UIText> textPtr = std::make_unique<UIText>(sf::IntRect(74, 0, 50, 50), "archive.otf");
	std::string testText = "Game";
	textPtr->setText(testText);
	textPtr->setColor(sf::Color(255, 92, 56));
	m_canvas->addElement(std::move(textPtr));
	//back button
	std::unique_ptr<UIButton> optionsBtnPtr = std::make_unique<UIButton>(sf::IntRect(10, 10, 64, 64),
		"defaultBackButton.png", "hoverBackButton.png", "pressedBackButton.png");
	optionsBtnPtr->addListener([this]() {m_gameDelegate.loadScene(new MainMenuScene(m_window, m_gameDelegate)); });
	m_canvas->addElement(std::move(optionsBtnPtr));
	//Actors
	std::unique_ptr<Actor> gameMapPtr = std::make_unique<GameMap>(3, 3, this);
	m_GameMapPtr = gameMapPtr.get();
	addActor(std::move(gameMapPtr));
	std::cout << "GameScene loaded\n";
}