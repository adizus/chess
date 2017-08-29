#ifndef PAWN
#define PAWN

#include "chessPiece.h"
#include "location.h"
#include <vector>


class Pawn :public ChessPiece {
	string name;
	bool isBlack;
	//Location* location;
	int row;
	int column;
	string defaultStartingPlace;
	vector <Location*> possibleMoves;
	bool isFirstMove = true;

public:
	Pawn(string name, bool isBlack, int row, int column) :ChessPiece(name, isBlack, row, column) {}
	bool isLegalMove(Location*,Game*);
	bool getIsFirstMove();
	void setIsFirstMove(bool);
	void promotePawn();

	//void eat();
	//void die();// call a destructor?
	//void findPossibleMoves();


};
#endif // !PAWN