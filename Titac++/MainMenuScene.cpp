#include "Scenes.h"

MainMenuScene::MainMenuScene(sf::RenderWindow& window, GameDelegate& gameDelegate) : Scene(window, gameDelegate)
{
}

void MainMenuScene::onInitialize()
{
	//title
	std::unique_ptr<UIText> textPtr = std::make_unique<UIText>(sf::IntRect(74, 0, 50, 50), "archive.otf");
	std::string testText = "Game Title";
	textPtr->setText(testText);
	textPtr->setColor(sf::Color(255, 92, 56));
	m_canvas->addElement(std::move(textPtr));

	std::unique_ptr<UIButton> startBtnPtr = std::make_unique<UIButton>(sf::IntRect(128, 145, 256, 88),
		"defaultStartButton.png", "hoverStartButton.png", "pressedStartButton.png");
	startBtnPtr->addListener([this]() {m_gameDelegate.loadScene(new GameScene(m_window, m_gameDelegate)); });
	m_canvas->addElement(std::move(startBtnPtr));
	std::unique_ptr<UIButton> optionsBtnPtr = std::make_unique<UIButton>(sf::IntRect(128, 248, 256, 88),
		"defaultOptionsButton.png", "hoverOptionsButton.png", "pressedOptionsButton.png");
	optionsBtnPtr->addListener([this]() {m_gameDelegate.loadScene(new OptionsScene(m_window, m_gameDelegate)); });
	m_canvas->addElement(std::move(optionsBtnPtr));
	std::unique_ptr<UIButton> exitBtnPtr = std::make_unique<UIButton>(sf::IntRect(128, 351, 256, 88),
		"defaultExitButton.png", "hoverExitButton.png", "pressedExitButton.png");
	exitBtnPtr->addListener([this]() {m_window.close(); });
	m_canvas->addElement(std::move(exitBtnPtr));
	std::cout << "MainMenuScene loaded\n";
}
