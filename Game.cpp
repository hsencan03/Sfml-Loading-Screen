#include "Game.hpp"

#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

Game::Game(unsigned int width, unsigned int height, std::string name) 
	: m_width{width}, m_height{height}, m_name{name}
{

}

void Game::run()
{
	//Showing loading screen
	loadingScreen();
	
	m_future = std::async(std::launch::async, [&]
	{
		return Setup();
	});

	GameLoop();
}

//Initialize only need for loading screen and others initialize in setup function
void Game::loadingScreen()
{
	m_window.create(sf::VideoMode(m_width, m_height), m_name);
	m_window.setFramerateLimit(30);

	if (!m_loadingTex.loadFromFile("assets/images/sencan.png"))
	{
		std::cout << " \"assets/images/sencan.png\" is not exsist\n";
	}
	m_loadingSpr.setTexture(m_loadingTex);
	m_loadingSpr.setScale(sf::Vector2f(0.3, 0.3));
	m_loadingSpr.setOrigin(m_loadingTex.getSize().x / 2, m_loadingTex.getSize().y / 2);
	m_loadingSpr.setPosition(m_width >> 1, (m_height >> 1) + m_loadingTex.getSize().y / 30);

	if (!m_animTex.loadFromFile("assets/images/loading.png"))
	{
		std::cout << " \"assets/images/loading.png\" is not exsist\n";
	}
	rect = sf::IntRect(0, 0, 188, 188);
	m_animSpr.setScale(0.3f, 0.3f);
	m_animSpr.setTexture(m_animTex);
	m_animSpr.setTextureRect(rect);
	m_animSpr.setOrigin((m_animTex.getSize().x * 0.3f) / 2, (m_animTex.getSize().y * 0.3f) / 2);
	m_animSpr.setPosition(m_width, m_height - 50);

	if (!m_loadingFont.loadFromFile("assets/fonts/komika-text_bold.ttf"))
	{
		std::cout << " \"assets/images/loading.png\" is not exsist\n";
	}
	m_loadingText.setFont(m_loadingFont);
	m_loadingText.setFillColor(sf::Color::Black);
	m_loadingText.setString("LOADING");
	m_loadingText.setCharacterSize(24);
	m_loadingText.setPosition(m_animSpr.getPosition().x - 225, m_animSpr.getPosition().y - m_loadingText.getCharacterSize());
}

//Initialize all you need in game
void Game::Setup()
{
	//Initialize here
	m_playText.setFont(m_loadingFont);
	m_playText.setCharacterSize(60);
	m_playText.setString("Game is running :)");
	m_playText.setFillColor(sf::Color::White);

	m_playText.setOrigin((m_playText.getCharacterSize() * m_playText.getString().getSize()) >> 1, m_playText.getCharacterSize() >> 1);

	m_playText.setPosition(m_width, m_height >> 1);

	//Waiting 10 seconds 
	std::this_thread::sleep_for(10s);
	
	//After initializing return
	return;
}

//Simple GameLoop
void Game::GameLoop()
{
	while (m_window.isOpen())
	{
		update();
		draw();
	}
}

void Game::update()
{
	m_status = m_future.wait_for(0ms);
	//Still Running
	if (m_status != std::future_status::ready)
	{
		if (rect.left < 2256 - 188)
			rect.left += 188;
		else
		{
			if (rect.top < 752 - 188)
				rect.top += 188;
			else
				rect.top = 0;

			rect.left = 0;
		}

		m_animSpr.setTextureRect(rect);
	}
	//Game is playing here!!!
	else
	{
		std::cout << "Playing\n";
	}
}

void Game::draw()
{
	//Still running draw loading screen
	if (m_status != std::future_status::ready)
	{
		m_window.clear(sf::Color::White);

		m_window.draw(m_loadingSpr);
		m_window.draw(m_animSpr);
		m_window.draw(m_loadingText);

		m_window.display();
	}
	//Game is playing here!!!
	else
	{
		m_window.clear();

		m_window.draw(m_playText);

		m_window.display();
	}
}
