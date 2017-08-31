#include "stdafx.h"
#include "chesspiece.h"
#include "pawn.h"
#include "location.h"

bool Pawn::getIsFirstMove() {
	return isFirstMove;
}

void Pawn::setIsFirstMove(bool isFirstMove) {
	this->isFirstMove = isFirstMove;
}

bool Pawn::isLegalMove(Location* to, Game* game) {//well I believe this function works but I don't think it is very readable
	bool legalMove = false;

	//need to add make sure nobody block first double move

	if (this->getIsBlack()) {
		if (!game->getPieceInLocation(to) && to->getColumn() == this->getColumn()) {
			if (to->getRow() == this->getRow() + 1 || to->getRow() == this->getRow() + 2 && this->getIsFirstMove()) {		
				legalMove = true;
			}
		}
		else if (game->getPieceInLocation(to)) {
			if (to->getRow() == this->getRow() + 1) {
				if (to->getColumn() == this->getColumn() + 1 || to->getColumn() == this->getColumn() - 1) {
					if (!game->getPieceInLocation(to)->getIsBlack()) {
						legalMove = true;
					}
				}
			}
		}
	}

	else {
		if (!game->getPieceInLocation(to) && to->getColumn() == this->getColumn()) {
			if (to->getRow() == this->getRow() - 1 || to->getRow() == this->getRow() - 2 && this->getIsFirstMove()) {
				legalMove = true;
			}
		}
		else if (game->getPieceInLocation(to)) {
			if (to->getRow() == this->getRow() - 1) {
				if (to->getColumn() == this->getColumn() + 1 || to->getColumn() == this->getColumn() - 1) {
					if (game->getPieceInLocation(to)->getIsBlack()) {
						legalMove = true;
					}
				}
			}
		}
	}


	return legalMove;
}

void Pawn::promotePawn() {
	string input;
	/*	if (this->getRow() == boardwidth || 0) {
	cout << "please choose a promotion: queen, knight, rook or bishop" << endl;
	}
	*/
}


ChessPiece* Pawn::copy() {
	return new Pawn(this->name, this->isBlack, this->row, this->column);
}




