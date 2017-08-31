#include "stdafx.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"

bool Queen::isLegalMove(Location* to,Game*game) {
	bool legalMove;

	Rook *dummyRook = new Rook(this->getName(),this->getIsBlack(), this->getRow(),this->getColumn());
	Bishop *dummyBishop = new Bishop(this->getName(), this->getIsBlack(), this->getRow(), this->getColumn());

	if (dummyRook->isLegalMove(to,game) || dummyBishop->isLegalMove(to,game))
		legalMove = true;
	else
		legalMove = false;

	delete dummyBishop;
	delete dummyRook;
	return legalMove;
}

ChessPiece* Queen::copy() {
	return new Queen(this->name, this->isBlack, this->row, this->column);
}

