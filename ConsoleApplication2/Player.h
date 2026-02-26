#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

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
    std::map<std::string, sf::Texture> textureCache;

public:
    Player(int hp, float speed, int damage) 
    {
        this->hp = hp;
        this->speed = speed;
		this->damage = damage;
        loadTextures("Run", 8);
        loadTextures("Idle", 2);
    }

    void loadTextures(std::string animName, int count) {
        for (int i = 1; i <= count; ++i) {
            std::string fileName = path + animName + std::to_string(i) + ".png";
            sf::Texture tex;
            if (tex.loadFromFile(fileName)) {
                // "Run1", "Run2" 같은 이름으로 맵에 저장
                textureCache[animName + std::to_string(i)] = tex;
            }
        }
    }
    void draw(sf::RenderWindow& window) {
        std::string currentKey = anim + std::to_string(currentFrame);

        if (textureCache.find(currentKey) != textureCache.end()) {
            sf::Sprite sprite(textureCache[currentKey]);
            sprite.setPosition({ player_x, player_y });
            sprite.setScale({ 5.f, 5.f });
            window.draw(sprite);
        }
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

    void move(float x)
    {
		if (player_x < -25) {
            player_x = -25; // 왼쪽 벽에 고정
        }

        if (player_x> 675) {
            player_x = 675; // 오른쪽 벽에 고정
        }
        player_x += (x* speed);
	}
};