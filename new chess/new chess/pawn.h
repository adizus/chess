#ifndef PAWN
#define PAWN

#include "chessPiece.h"
#include "location.h"
#include <vector>
	
	

class Pawn :public ChessPiece {
	
	bool isFirstMove = true;

public:
	Pawn(string name, bool isBlack, int row, int column) :ChessPiece(name, isBlack, row, column) {}
	bool isLegalMove(Location*,Game*);
	bool getIsFirstMove();
	void setIsFirstMove(bool);
	void checkAndExecutePawnPromotion(Game*game);
	ChessPiece* copy();

	//void eat();
	//void die();// call a destructor?
	

};
#endif // !PAWN