// newchess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game.h"
#include <iostream>

int main() {
	Game *chess = new Game();
	chess->play();
	int a;
	cin >> a;
}