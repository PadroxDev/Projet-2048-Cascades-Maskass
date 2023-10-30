#include "Utility.h"

namespace Utility {
	void initUtility() {
		output = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void setColorToValue(int value) {
		Colors color = valuesToColors[value];
		changeOutputColor(color);
	}

	void repeatCharacter(char c, int n) {
		std::cout << std::string(n, c);
	}

	unsigned int countIntegerDigits(int number) {
		unsigned int numberOfDigits = 0;

		do {
			++numberOfDigits;
			number /= 10;
		} while (number);
		return numberOfDigits;
	}

	void changeOutputColor(Colors color) {
		SetConsoleTextAttribute(output, color);
	}

	void resetOutputColor() {
		SetConsoleTextAttribute(output, Colors::WHITE);
	}

	void lowerString(std::string& s) {
		for (char& c : s)
		{
			c = tolower(c);
		}
	}

	void clearConsole() {
		system("cls");
	}
}