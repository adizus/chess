// newchess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game.h"
#include <iostream>
int objectCounter = 0;


int main() {
	Game *chess = new Game();
	chess->play();
	int a;
	cin >> a;
}