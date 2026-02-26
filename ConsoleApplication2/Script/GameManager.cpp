#pragma once
#include <SFML/Graphics.hpp>
#include	"Player.h"
#include "Time.h"

bool isRunning = true;

int  w = 800;
int h = 600;


int main()
{
	sf::Clock clock;
	sf::RenderWindow window;

	// hp/speed/damage
	Player player(100, 5.0f, 10);
	window.create(sf::VideoMode({ 800,600 }), "SFML window");
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		Time time(GameManager::getInstance().getGameTime());

		while (const std::optional event = window.pollEvent())
		{
			if (event->is < sf::Event::Closed >())
			{
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player.move(-1.0f);
			player.animate("Run",8, 0.08f);
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.move(1.0f);
			player.animate("Run",8, 0.08f);
		}
		else {
			player.animate("Idle",2, 0.5f);

		}
		window.clear(sf::Color::White);
		player.draw(window);
		time.draw(window);
		window.display();
	}
}


