#pragma once

#include <string>
#include <iostream>
#include "Utility.h";

using namespace std;

static void rainbowText(string text) {
	for (char& c : text) {
		int color = rand() % 13 + 1;
		Utility::changeOutputColor((Colors)color);
		cout << c;
	}
}

static void showChooseMoveText() {
	Utility::resetOutputColor();
	cout << endl << "Choose a ";
	Utility::changeOutputColor(Colors::LIGHT_BLUE);
	cout << " direction ";
	Utility::resetOutputColor();
	cout << "to shift tiles towards using the ";
	Utility::changeOutputColor(Colors::GREEN);
	cout << "arrow keys";
	Utility::resetOutputColor();
	cout << " !" << endl;
}

static void showVictoryText() {
	rainbowText("Well done it's WON! ");
	Utility::resetOutputColor();
	cout << endl << "You ";
	Utility::changeOutputColor(Colors::OCHRE);
	cout << "successfully ";
	Utility::resetOutputColor();
	cout << "made a ";
	Utility::setColorToValue(2048);
	cout << "2048";
	Utility::resetOutputColor();
	cout << " !";
}

static void showDefeatText() {
	Utility::resetOutputColor();
	cout << endl << "Oh no... You've ";
	Utility::changeOutputColor(Colors::RED);
	cout << "LOST !";
}