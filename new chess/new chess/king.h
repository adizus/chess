#ifndef KING
#define KING

#include "chessPiece.h"
#include "location.h"
#include <vector>
#include <iostream>

class King :public ChessPiece {
	
	bool isFirstMove = true;

public:
	King(string name, bool isBlack, int row, int column) :ChessPiece(name, isBlack, row, column) {}
	bool isLegalMove(Location*, Game*);
	bool getIsFirstMove();
	void setIsFirstMove(bool);
	ChessPiece* copy();
	//void eat();
	//void die();// call a destructor?
	

};
#endif
