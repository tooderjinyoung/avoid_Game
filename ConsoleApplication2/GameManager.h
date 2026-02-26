#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iomanip> 
#include <cmath>
#include <iostream>


#include "Time.h"
#include "GameManager.h"

using namespace std;
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
	float getDeltaTime() const {
		return deltaTime;
	}
	// 게임 전체 경과 시간을 가져오는 함수입니다.
	float getGameTime(){
		gameTime += deltaTime; // 게임 시간 누적
		return gameTime;
	}
};