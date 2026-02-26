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
	GameManager() {
		if (!font.openFromFile("font/NEXON_Lv1_Gothic/NEXON Lv1 Gothic_OTF_TTF/TTF/NEXONLv1GothicRegular.ttf")) {
			// 폰트 로드 실패 시 처리 (에러 메시지 출력 등)
		}
	} // 생성자 숨기기
	sf::Clock clock;
	float deltaTime = 0.01f;

	float gameTime = 0;
	sf::Font font;
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
		deltaTime = clock.restart().asSeconds();
		if (isRunning) {
			gameTime += deltaTime;
		}
	}

	// 다른 클래스에서 현재 프레임의 시간을 가져갈 때 사용합니다.
	float getDeltaTime(){
		return deltaTime;
	}
	// 게임 전체 경과 시간을 가져오는 함수입니다.
	float getGameTime(){
		if (!isRunning) return gameTime;
	}

	void textDraw(sf::RenderWindow& window,std::string String, int size, float posx, float posy,sf:: Color color)
	{
		// 3. "MM:SS" 형식의 문자열 생성
		std::string timeString = String;

		sf::Text text(font, timeString, size);
		sf::FloatRect textBounds = text.getLocalBounds();

		text.setOrigin(textBounds.getCenter());
		text.setFillColor(color);
		text.setPosition({ posx,posy });
		// 5. 텍스트를 창에 그리기
		window.draw(text);

	}
};