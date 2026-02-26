#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "GameManager.h"

class Player {
private:
    float player_x = 320.0f; // 800x600 창 기준 가로 중앙 (5배 확대 고려)
    float player_y = 440.0f; // 바닥 지점 (5배 확대 고려)

    std::string path = "Sprite/";
    std::string anim = "Run";

    int currentFrame = 1;
    float animTimer = 0.0f;
    float frameTime = 0.2f;

    int frameCount =1;

	int hp;
	float speed;
	int damage;

public:
    Player(int hp, float speed, int damage) 
    {
        this->hp = hp;
        this->speed = speed;
		this->damage = damage;
    
    }

    void animation() {
        animTimer += GameManager::getInstance().getDeltaTime();
        if (animTimer >= frameTime) {
            currentFrame++;

            animTimer = 0.0f;
		}
    }
    void animate(sf::String anim,int frameCount,float frameTime) {

         this->anim = anim;
         this->frameCount = frameCount;
         this->frameTime = frameTime;
         if (currentFrame >= frameCount) {
             currentFrame = 1;
         }

         animation();
    }
    void draw(sf::RenderWindow& window)
    {
        sf::Texture texture;
            
            if (!texture.loadFromFile(path +anim+ std::to_string(currentFrame) + ".png"))
            {
				printf("Error loading texture\n");
            }
            sf::Sprite sprite(texture);
            sprite.setPosition(sf::Vector2f(player_x, player_y));
            sprite.setScale({ 5.f,5.f });
            window.draw(sprite);
	}

    void move(float x)
    {
        player_x += (x* speed);
	}




};