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

    void setHp(int hp)
    {
        this->hp = hp;
        this->speed += 1;

    }
    int getHp()
    {
        return this->hp;
    }
    void setspeed(float speed)
    {
        this->speed =speed;
    }
    float getspeed()
    {
        return this->speed;
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
    sf::FloatRect getGlobalBounds() {
        std::string currentKey = currentAnimName + std::to_string(currentFrame);

        if (textureCache.count(currentKey)) {
            sf::Texture& tex = textureCache[currentKey];
            // 위치(posX, posY)와 실제 그려지는 크기(텍스처 크기 * 5배 스케일)를 계산
            return sf::FloatRect({ posX, posY }, { tex.getSize().x * 5.f, tex.getSize().y * 5.f });
        }

        return sf::FloatRect({ posX, posY }, { 0, 0 }); // 텍스처가 없을 때 예외 처리
    }

    void dead(sf::RenderWindow& window)
    {
        window.clear();
        GameManager::getInstance().textDraw(window, "GAMEOVER", 80, 400, 250, sf::Color::Red);
    }

    void drawDebug(sf::RenderWindow& window) {
        // 1. 위에서 만든 getGlobalBounds()로 영역 가져오기
        sf::FloatRect bounds = getGlobalBounds();

        // 2. SFML 3.0 방식의 RectangleShape 생성
        sf::RectangleShape debugRect(bounds.size); // 크기 설정
        debugRect.setPosition(bounds.position);   // 위치 설정

        // 3. 모양 설정 (속은 비우고 테두리만)
        debugRect.setFillColor(sf::Color::Transparent);
        debugRect.setOutlineColor(sf::Color::Green);    // 잘 보이게 초록색
        debugRect.setOutlineThickness(2.0f);            // 테두리 두께

        // 4. 화면에 그리기
        window.draw(debugRect);
    }



};