#include "stdafx.h"
#include "chessPiece.h"
#include "location.h "
#include "knight.h"

bool Knight::isLegalMove(Location* to,Game * game) {

	if (to->getRow() + 1 == this->getRow() && to->getColumn() + 2 == this->getColumn() ||
		to->getRow() + 1 == this->getRow() && to->getColumn() - 2 == this->getColumn() ||
		to->getRow() - 1 == this->getRow() && to->getColumn() + 2 == this->getColumn() ||
		to->getRow() - 1 == this->getRow() && to->getColumn() - 2 == this->getColumn() ||
		to->getRow() + 2 == this->getRow() && to->getColumn() + 1 == this->getColumn() ||
		to->getRow() + 2 == this->getRow() && to->getColumn() - 1 == this->getColumn() ||
		to->getRow() - 2 == this->getRow() && to->getColumn() + 1 == this->getColumn() ||
		to->getRow() - 2 == this->getRow() && to->getColumn() - 1 == this->getColumn())

		return true;
	else
		return false;
}


ChessPiece* Knight::copy() {
	return new Knight(this->name, this->isBlack, this->row, this->column);
}




