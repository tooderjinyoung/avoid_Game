#pragma once
#include "Animation.h"

class Player : public Animation {
private:
    std::string currentAnimName = "Run";

public:
    Player(int hp, float speed, int damage) {
        this->hp = hp;
        this->speed = speed;
        this->damage = damage;
        this->posX = 320.0f;
        this->posY = 440.0f;

        loadTextures("Run", 8);
		loadTextures("Idle",2);
    }
    void draw(sf::RenderWindow& window) override {
        std::string currentKey = currentAnimName + std::to_string(currentFrame);
        if (textureCache.count(currentKey)) {
            sf::Sprite sprite(textureCache[currentKey]);
            sprite.setPosition({ posX, posY });
            sprite.setScale({ 5.f, 5.f });
            window.draw(sprite);
        }
    }

    // 인터페이스 move()와 맞춤. 실제 x 이동은 내부 로직이나 별도 함수로!
    void move() override {
        if (posX < -25) posX = -25;
        if (posX > 675) posX = 675;
    }

    // 조작을 위한 추가 함수
    void handleInput(float x) {
        posX += (x * speed);
        move(); // 벽 충돌 체크
    }
};