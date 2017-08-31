#ifndef CHESSPIECE
#define CHESSPIECE

#include <iostream>
#include <vector>
#include "location.h"
#include "game.h"
extern int objectCounter;


//board[row][column]
using namespace std;
class Game;


class ChessPiece {
	string name;
	bool isBlack;
	//Location* location;
	int row;//current place
	int column;//current place
	string defaultStartingPlace;
	
public:
	ChessPiece(string, bool, int row, int column);
	virtual ChessPiece* copy()=0;
	virtual bool isLegalMove(Location*,Game*) = 0;
	//virtual void eat()=0;
	//virtual void die()=0;//build a destructor? call a destructor?
	
	//virtual ~ChessPiece();
	virtual string getName();
	virtual bool getIsBlack();
	virtual int getColumn();
	virtual int getRow();
	virtual void setColumn(int);
	virtual void setRow(int);

};
#endif 
