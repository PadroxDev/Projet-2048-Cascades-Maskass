#pragma once

#include <string>
#include <windows.h>
#include <map>
#include <iostream>

namespace Input {
	const int KEY_UP = 72;
	const int KEY_DOWN = 80;
	const int KEY_LEFT = 75;
	const int KEY_RIGHT = 77;
}

enum Colors {
	DARK_BLUE = 1,
	GREEN = 2,
	LIGHT_BLUE = 3,
	DARK_RED = 4,
	PURPLE = 5,
	OCHRE = 6,
	LIGHT_GREY = 7,
	GREY = 8,
	BLUE = 9,
	NEON_GREEN = 10,
	TURQUOISE = 11,
	RED = 12,
	MAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

namespace Utility {
	static HANDLE output;
	static std::map<int, Colors> valuesToColors = {
		{2, Colors::LIGHT_BLUE},
		{4, Colors::OCHRE},
		{8, Colors::YELLOW},
		{16, Colors::DARK_RED},
		{32, Colors::RED},
		{64, Colors::GREEN},
		{128, Colors::PURPLE},
		{256, Colors::BLUE},
		{512, Colors::DARK_BLUE},
		{1024, Colors::TURQUOISE},
		{2048, Colors::NEON_GREEN},
		{4096, Colors::MAGENTA}
	};

	void initUtility();
	void setColorToValue(int value);
	void changeOutputColor(Colors color);
	void resetOutputColor();
	void clearConsole();
	void repeatCharacter(char c, int n);
	unsigned int countIntegerDigits(int number);
}