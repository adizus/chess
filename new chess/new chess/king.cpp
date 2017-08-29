#include "stdafx.h"
#include "king.h"
#include "chessPiece.h"
#include "location.h "
#include "game.h"

bool King::isLegalMove(Location* to,Game* game) {

	if (
		to->getRow() + 1 == this->getRow() && to->getColumn() + 1 == this->getColumn() ||
		to->getRow() + 1 == this->getRow() && to->getColumn() - 1 == this->getColumn() ||
		to->getRow() + 1 == this->getRow() && to->getColumn() == this->getColumn() ||
		to->getRow() == this->getRow() && to->getColumn() + 1 == this->getColumn() ||
		to->getRow() - 1 == this->getRow() && to->getColumn() + 1 == this->getColumn() ||
		to->getRow() - 1 == this->getRow() && to->getColumn() - 1 == this->getColumn() ||
		to->getRow() - 1 == this->getRow() && to->getColumn() == this->getColumn() ||
		to->getRow() == this->getRow() && to->getColumn() - 1 == this->getColumn())

		return true;
	else
		return false;
}


bool King::getIsFirstMove() {
	return isFirstMove;
}

void King::setIsFirstMove(bool isFirstMove) {
	this->isFirstMove = isFirstMove;
}


