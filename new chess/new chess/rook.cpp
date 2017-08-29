#include "stdafx.h"
#include "chessPiece.h"
#include "rook.h"
#include "location.h"
#include "game.h"



bool Rook::getIsFirstMove() {
	return isFirstMove;
}

void Rook::setIsFirstMove(bool isFirstMove) {
	this->isFirstMove = isFirstMove;
}

bool Rook::isLegalMove(Location* to,Game* game) {
	int dif;
	bool legalMove = false;
	if (to->getRow() == this->getRow() && to->getColumn() != this->getColumn() ||
		to->getRow() != this->getRow() && to->getColumn() == this->getColumn())
	{

		legalMove = true;

		dif = to->getRow() - this->getRow();// make sure dif is synced with loops of i movements

		if (dif > 0) {
			for (int i = 1; i < dif && legalMove; i++) {
				if (game->getPieceInLocation(this->getRow() + i, this->getColumn()))
					legalMove = false;
			}
		}
		else if (dif < 0) {
			for (int i = -1; i > dif && legalMove; i--) {
				if (game->getPieceInLocation(this->getRow() + i, this->getColumn()))
					legalMove = false;
			}

		}
		else {
			dif = to->getColumn() - this->getColumn();
			if (dif > 0) {
				for (int i = 1; i < dif && legalMove; i++) {
					if (game->getPieceInLocation(this->getRow(), this->getColumn() + i))
						legalMove = false;
				}
			}
			else if (dif < 0) {
				for (int i = -1; i > dif && legalMove; i--) {
					if (game->getPieceInLocation(this->getRow(), this->getColumn() + i))
						legalMove = false;
				}
			}
		}
	}
	return legalMove;
}









