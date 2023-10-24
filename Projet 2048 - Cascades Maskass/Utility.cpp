#include "Utility.h"

namespace Utility {
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