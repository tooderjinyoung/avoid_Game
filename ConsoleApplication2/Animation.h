#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "GameManager.h"

class Animation {
protected:
    int currentFrame = 1;
    float animTimer = 0.0f;
    float frameTime = 0.2f;
    int frameCount = 1;

    float posX = 0, posY = 0;
    int hp = 0, damage = 0;
    float speed = 0;
    std::string path = "Sprite/";

    std::string anim = "Run";


    float gravity = 0.01f;
    std::map<std::string, sf::Texture> textureCache;

    // 내부 로직 함수 (가상이 아님)
    void updateAnimationTimer() {
        animTimer += GameManager::getInstance().getDeltaTime();
        if (animTimer >= frameTime) {
            currentFrame++;
            animTimer = 0.0f;
        }
    }

public:
    virtual ~Animation() {}


    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move() = 0;
    void loadTextures(std::string animName, int count)
    {
        for (int i = 1; i <= count; ++i) {
            std::string fileName = path + animName + std::to_string(i) + ".png";
            sf::Texture tex;
            if (tex.loadFromFile(fileName)) {
                textureCache[animName + std::to_string(i)] = tex;
            }
        }
    }

    void animate(sf::String anim, int frameCount, float frameTime) {

        this->anim = anim;
        this->frameCount = frameCount;
        this->frameTime = frameTime;
        if (currentFrame >= frameCount) {
            currentFrame = 1;
        }

        updateAnimationTimer();
    }



};