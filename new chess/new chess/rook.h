#ifndef ROOK
#define ROOK

#include "chessPiece.h"
#include "location.h"
#include <vector>

class Rook :public ChessPiece {
	string name;
	bool isBlack;
	int row;
	int column;
	string defaultStartingPlace;
	vector <string> possibleMoves;
	bool isFirstMove = true;

public:
	Rook(string name, bool isBlack, int row, int column) :ChessPiece(name, isBlack, row, column) {}
	Rook() {};
	bool isLegalMove(Location*, Game*);
	bool getIsFirstMove();
	void setIsFirstMove(bool);
	//void eat();
	//void die();// call a destructor?
	//void findPossibleMoves();

};
#endif // !ROOK



