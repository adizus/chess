#ifndef BISHOP
#define BISHOP


#include "chessPiece.h"
#include "location.h"


class Bishop :public ChessPiece {
	
public:
	Bishop(string name, bool isBlack, int row, int column) :ChessPiece(name, isBlack, row, column) {}
	bool isLegalMove(Location*, Game*);
	ChessPiece* copy();
	//void eat();
	//void die();// call a destructor?
	//void findPossibleMoves();

};

#endif 