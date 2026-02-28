#pragma once

#include <string>
#include <SFML/Graphics.hpp>
class Time
{
	private:

		int minutes = 0;
		int seconds = 0;
	public:
		Time() {
			
			this->minutes = 0;
			this ->seconds = 0;
		}

		std::string getTimeString(float totalSeconds)
		{
			int total = static_cast<int>(totalSeconds);
			this->minutes = total / 60;
			this->seconds = total % 60;

			return (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
				(seconds < 10 ? "0" : "") + std::to_string(seconds);
		}

		int getMinutes(){
			return minutes;
		}
		int getSeconds() {
			return seconds;
		}

};

