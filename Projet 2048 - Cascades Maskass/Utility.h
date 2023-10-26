#pragma once

#include <string>

namespace Input {
	const int KEY_UP = 72;
	const int KEY_DOWN = 80;
	const int KEY_LEFT = 75;
	const int KEY_RIGHT = 77;
}

namespace Utility {
	void lowerString(std::string& s);
	void clearConsole();
}