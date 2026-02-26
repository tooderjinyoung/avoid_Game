#pragma once
#include <SFML/Graphics.hpp>
#include	"Player.h"
#include "Time.h"
#include <string>


int  w = 800;
int h = 600;



int main()
{
	
	sf::Clock clock;
	sf::RenderWindow window;
	Time time;

	// hp/speed/damage
	Player player(100, 5.0f, 10);
	window.create(sf::VideoMode({ 800,600 }), "avoid Game");
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		GameManager::getInstance().update();
		sf::String currentTime = time.getTimeString(GameManager::getInstance().getGameTime());


		while (const std::optional event = window.pollEvent())
		{
			// 2. 이벤트가 '키 눌림(KeyPressed)'인지 확인합니다.
			if (event->is<sf::Event::KeyPressed>())
			{
				// 3. 실제 키 데이터를 가져옵니다.
				const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();

				// 4. 어떤 키가 눌렸는지 확인합니다 (예: Space)
				if (keyPressed->code == sf::Keyboard::Key::Space)
				{
					isRunning = !isRunning;
				}
			}
			if (event->is < sf::Event::Closed >())
			{
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && isRunning) {
			player.move(-1.0f);
			player.animate("Run",8, 0.1f);
			
			}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && isRunning) {
			player.move(1.0f);
			player.animate("Run",8,0.1f);
			}
		else {
			player.animate("Idle", 2, 0.5f);
		}
		window.clear(sf::Color::White);
		if (!isRunning)		GameManager::getInstance().textDraw(window, "Pasue", 80, 400, 250, sf::Color::Red);
		GameManager::getInstance().textDraw(window,currentTime, 50, 400, 20, sf::Color::Black);
		player.draw(window);
		window.display();
	}
}


