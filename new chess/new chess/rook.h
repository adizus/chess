#ifndef ROOK
#define ROOK

#include "chessPiece.h"
#include "location.h"
#include <vector>

class Rook :public ChessPiece {
	
	bool isFirstMove = true;

public:
	Rook(string name, bool isBlack, int row, int column) :ChessPiece(name, isBlack, row, column) {}
	
	bool isLegalMove(Location*, Game*);
	bool getIsFirstMove();
	void setIsFirstMove(bool);
	ChessPiece* copy();
	//void eat();
	//void die();// call a destructor?
	
};
#endif // !ROOK



