#ifndef KNIGHT
#define KNIGHT
 

#include "chessPiece.h"
#include "location.h"
#include <vector>


class Knight :public ChessPiece {
	string name;
	bool isBlack;
	int row;
	int column;
	string defaultStartingPlace;
	vector <string> possibleMoves;

public:
	Knight(string name, bool isBlack,int row, int column) :ChessPiece(name, isBlack,row, column) {}
	bool isLegalMove(Location*,Game*);
	//void eat();
	//void die();// call a destructor?
	//void findPossibleMoves();

};
#endif