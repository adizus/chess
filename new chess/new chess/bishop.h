#ifndef BISHOP
#define BISHOP


#include "chessPiece.h"
#include "location.h"


class Bishop :public ChessPiece {
	string name;
	bool isBlack;
	int row;
	int column;
	string defaultStartingPlace;
	vector <Location*> possibleMoves;

public:
	Bishop(string name, bool isBlack, int row, int column) :ChessPiece(name, isBlack, row, column) {}
	bool isLegalMove(Location*, Game*);
	Bishop() {}
	//void eat();
	//void die();// call a destructor?
	//void findPossibleMoves();

};

#endif 