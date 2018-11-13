#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <future>
#include <string>

class Game{
public:
	Game(unsigned int width, unsigned int height, std::string name);

	void run();

private:
	void loadingScreen();

	void Setup();

	void GameLoop();

	void update();

	void draw();

private:
	unsigned int m_width, m_height;
	std::string m_name;
	sf::RenderWindow m_window;

	std::future<void> m_future;
	std::future_status m_status;

	sf::Texture m_loadingTex;
	sf::Sprite m_loadingSpr;

	sf::Texture m_animTex;
	sf::Sprite m_animSpr;
	sf::IntRect rect;

	sf::Font m_loadingFont;
	sf::Text m_loadingText;
	sf::Text m_playText;
};