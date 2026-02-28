#pragma once
#include "Animation.h"
#include <random>



class Frame : public Animation {

public:
    bool isGround = false;

    Frame(int hp, int damage, float speed) {
        this->hp = hp;
        this->damage = damage;
        this->speed = speed;

        // 1. 경로 및 애니메이션 이름 설정 (Animation 클래스의 변수 활용)
        this->path = "Sprite/";
        this->anim = "Frame/FlameAxe_";

        this->posX = randomSeed(-25.0f, 675.0f);
        this->posY = -20.0f;

        // 텍스처 로드
        loadTextures(this->anim, 18);
    }

    void draw(sf::RenderWindow& window) override {
        std::string currentKey = anim + std::to_string(currentFrame);

        if (textureCache.find(currentKey) != textureCache.end()) {
            sf::Sprite sprite(textureCache[currentKey]);
            sprite.setPosition({ posX, posY });
            sprite.setRotation(sf::degrees(90.0f));
            sprite.setScale({ 5.f, 5.f });

            window.draw(sprite);

            // 3. 애니메이션 상태 업데이트 (프레임 넘기기)
            // 18프레임까지 0.1초 간격으로 재생
            animate(this->anim, 18, 0.1f);
        }
    }

    void move() override {
        speed += gravity;
        posY += speed;
        if (speed > 10.0f) speed = 10.0f;
    }

    float randomSeed(float left, float right) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(left, right);
        return dis(gen);
    }
};