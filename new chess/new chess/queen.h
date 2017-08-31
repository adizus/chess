#ifndef QUEEN
#define QUEEN



#include "chessPiece.h"
#include "location.h"
#include <vector>


class Queen :public ChessPiece {
	string name;
	bool isBlack;
	int row;
	int column;

public:
	Queen(string name, bool isBlack, int row, int column) :ChessPiece(name, isBlack, row, column) {}
	bool isLegalMove(Location*, Game*);
	ChessPiece* copy();
	//void eat();
	//void die();// call a destructor?
	
};
#endif // !QUEEN
