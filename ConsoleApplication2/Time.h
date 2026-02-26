#pragma once

#include <string>
#include <SFML/Graphics.hpp>
class Time
{
private:

	int minutes;
	int seconds;


public:
	Time(float totalSeconds) {
		// 1. 실수형 초를 정수로 변환 (소수점 아래는 버림)
		int total = static_cast<int>(totalSeconds);
		// 2. 분과 초 계산
		this->minutes = total / 60;
		this->seconds = total % 60;
	}

	void draw(sf::RenderWindow& window) {
		// 3. "MM:SS" 형식의 문자열 생성
		std::string timeString = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
			(seconds < 10 ? "0" : "") + std::to_string(seconds);
		// 4. SFML 텍스트 객체 생성 및 설정
		sf::Font font;
		if (!font.openFromFile("font/NEXON_Lv1_Gothic/NEXON Lv1 Gothic_OTF_TTF/TTF/NEXONLv1GothicRegular.ttf")) {
			// 폰트 로드 실패 시 처리 (에러 메시지 출력 등)
		}
		sf::Text text(font, timeString, 36); // 글자 크기 24
		sf::FloatRect textBounds = text.getLocalBounds();

		// 2. 텍스트 자체의 중심점(Origin)을 텍스트의 정중앙으로 설정합니다.
		// getCenter()는 SFML 3에서 제공하는 아주 편리한 헬퍼 함수입니다.
		text.setOrigin(textBounds.getCenter());
		text.setFillColor(sf::Color::Black); // 글자 색상 흰색
		text.setPosition({ 400.f, 20.f }); // 화면 왼쪽 상단에 위치
		// 5. 텍스트를 창에 그리기
		window.draw(text);
	}


};

