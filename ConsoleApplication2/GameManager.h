#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iomanip> 
#include <cmath>
#include <iostream>


#include "Time.h"
#include "GameManager.h"

using namespace std;
bool isRunning = true;
class GameManager {
private:
	GameManager() {} // 생성자 숨기기
	sf::Clock clock;
	float deltaTime = 0.01f;

	float gameTime = 0;


public:
	// 싱글톤 인스턴스 가져오기
	static GameManager& getInstance() {
		static GameManager instance;
		return instance;
	}

	// 복사 방지
	GameManager(const GameManager&) = delete;
	void operator=(const GameManager&) = delete;

	// 매 프레임마다 호출하여 시간을 업데이트합니다.
	void update() {
		// restart()는 지난 프레임 이후 흐른 시간을 반환하고 시계를 0으로 리셋합니다.
		deltaTime = clock.restart().asSeconds();
	}

	// 다른 클래스에서 현재 프레임의 시간을 가져갈 때 사용합니다.
	float getDeltaTime(){
		return deltaTime;
	}
	// 게임 전체 경과 시간을 가져오는 함수입니다.
	float getGameTime(){
		if (!isRunning) return gameTime; // 게임이 멈춰있다면 현재까지 누적된 시간 반환

		gameTime += deltaTime; // 게임 시간 누적
		return gameTime;
	}
	void PauseDraw(sf::RenderWindow& window)
	{
		if (isRunning) return;
		std::string timeString = "Pause";
		// 4. SFML 텍스트 객체 생성 및 설정
		sf::Font font;
		if (!font.openFromFile("font/NEXON_Lv1_Gothic/NEXON Lv1 Gothic_OTF_TTF/TTF/NEXONLv1GothicRegular.ttf")) {
			// 폰트 로드 실패 시 처리 (에러 메시지 출력 등)
		}

		sf::Text text(font, timeString, 100); // 글자 크기 24


		sf::FloatRect textBounds = text.getLocalBounds();

		text.setOrigin(textBounds.getCenter());

		text.setFillColor(sf::Color::Red); 
		text.setPosition({ 400.0f,250 });

		window.draw(text);
	}
};