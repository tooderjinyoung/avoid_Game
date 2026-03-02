#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Frame.h"
#include <vector>
#include "Time.h"
#include <string>

int w = 800;
int h = 600;
bool isRunning = false;
std::vector<Frame*> frames;
sf::String currentTime;

void Spawner(float deltaTime, std::vector<Frame*>& frames)
{
    static float timer = 0.0f;
    float spawnDelay = 0.7f; // 0.7초마다 생성

    if (isRunning)
    {
        timer += deltaTime; // 누적 시간 계산

        if (timer >= spawnDelay)
        {
            for (auto* frame : frames)
            {
                if (frame->isGround) // 노는 객체 찾기
                {
                    frame->isGround = false;
                    frame->Posformat(); // 위치 초기화
                    timer = 0.0f; // 타이머 리셋
                    break;
                }
            }
        }
    }
}

int main()
{
    sf::RenderWindow window;



    Player player(10, 5.0f, 10);
    window.create(sf::VideoMode({ 800, 600 }), "avoid Game");
    window.setFramerateLimit(60);
    isRunning = false;
    Time time;
    sf::Clock clock;
    for (int i = 0; i < 20; i++)
    {
        Frame* f = new Frame(1,1,1.0f+i);
        f->isGround = true;
        frames.push_back(f);
    }

    while (window.isOpen())
    {

        if (player.getHp() <= 0) break;
        float dt = clock.restart().asSeconds();

        GameManager::getInstance().update();
        currentTime = time.getTimeString(GameManager::getInstance().getGameTime());

        Spawner(dt, frames);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::KeyPressed>())
            {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                if (keyPressed->code == sf::Keyboard::Key::Space) isRunning = !isRunning;
            }
            if (event->is<sf::Event::Closed>()) window.close();
        }

        if (isRunning)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                player.handleInput(-1.0f);
                player.animate("Run", 8, 0.1f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                player.handleInput(1.0f);
                player.animate("Run", 8, 0.1f);
            }
            else player.animate("Idle", 2, 0.5f);
        }

        window.clear(sf::Color::White);

        if (!isRunning) GameManager::getInstance().textDraw(window, "Pause", 80, 400, 250, sf::Color::Red);
        GameManager::getInstance().textDraw(window, currentTime, 50, 400, 20, sf::Color::Black);
        GameManager::getInstance().textDraw(window, "HP : " + std::to_string(player.getHp()), 50, 100, 20, sf::Color::Black);

        for (auto* frame : frames)
        {
            if (!frame->isGround)
            {
                frame->draw(window);
                frame->animate("Frame/FlameAxe_", 18, 0.1f);

                if (isRunning) frame->move();

                if (player.getGlobalBounds().findIntersection(frame->getGlobalBounds()))
                {
                    player.setHp(player.getHp() - 1);
                    frame->isGround = true;
                    frame->Posformat();
                }

                if (frame->getPosY() > 600.0f)
                {
                    frame->isGround = true;
                    frame->Posformat();
                }
                frame->drawDebug(window);

            }
        }

        player.draw(window);
        player.drawDebug(window);
        window.display();

    }

    for (auto* frame : frames) delete frame;
    frames.clear();

    while (window.isOpen())
    {
        player.dead(window);
        window.display();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }
    }

    return 0;
}