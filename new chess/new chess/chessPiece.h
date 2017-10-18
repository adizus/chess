#ifndef CHESSPIECE
#define CHESSPIECE

#include <iostream>
#include <vector>
#include "location.h"
#include "game.h"


//board[row][column]
using namespace std;
class Game;


class ChessPiece {
	string name;
	bool isBlack;
	int row;//current place
	int column;//current place
	string defaultStartingPlace;
	
public:
	ChessPiece(string, bool, int row, int column);
	virtual ChessPiece* copy()=0;
	virtual bool isLegalMove(Location*,Game*) = 0;
	
	virtual string getName();
	virtual bool getIsBlack();
	virtual int getColumn();
	virtual int getRow();
	virtual void setColumn(int);
	virtual void setRow(int);

};
#endif 
