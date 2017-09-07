#include "stdafx.h"
#include "chesspiece.h"
#include "pawn.h"
#include "location.h"
#include "global.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"


bool Pawn::getIsFirstMove() {
	return isFirstMove;
}

void Pawn::setIsFirstMove(bool isFirstMove) {
	this->isFirstMove = isFirstMove;
}


bool Pawn::isLegalMove(Location* to, Game* game) {
	bool legalMove = false;

	if (game->getEnPassantLocation())
		if (!(*to == *(game->getEnPassantLocation())))//if this move is not going to use the en passant, it will not be saved to the next round
			game->setEnPassantLocation();//set to null

	if (this->getIsBlack()) {
		if (!game->getPieceInLocation(to) && to->getColumn() == this->getColumn()) {
			if (to->getRow() == this->getRow() + 1)
				legalMove = true;
			else if (to->getRow() == this->getRow() + 2 && this->getIsFirstMove()) {
				if (game->getPieceInLocation(this->getRow() + 1, this->getColumn()) == NULL) {
					legalMove = true;
					game->setEnPassantLocation(this->getRow() + 1, this->getColumn());
				}
			}
		}
		else if (game->getPieceInLocation(to) || game->getEnPassantLocation() != NULL)
			if (to->getRow() == this->getRow() + 1)
				if (to->getColumn() == this->getColumn() + 1 || to->getColumn() == this->getColumn() - 1)
					legalMove = true;
	}

	//if piece is white:
	else {
		if (!game->getPieceInLocation(to) && to->getColumn() == this->getColumn()) {
			if (to->getRow() == this->getRow() - 1)
				legalMove = true;
			if (to->getRow() == this->getRow() - 2 && this->getIsFirstMove()) {
				if (game->getPieceInLocation(this->getRow() - 1, this->getColumn()) == NULL) {
					legalMove = true;
					game->setEnPassantLocation(this->getRow() - 1, this->getColumn());
				}
			}
		}
		else if (game->getPieceInLocation(to) || game->getEnPassantLocation() != NULL)
			if (to->getRow() == this->getRow() - 1)
				if (to->getColumn() == this->getColumn() + 1 || to->getColumn() == this->getColumn() - 1) 
					legalMove = true;
	}
	return legalMove;
}



void Pawn::checkAndExecutePawnPromotion(Game* game) {
	bool validInput = false;
	string input;
	ChessPiece* newPiece = NULL;
	if (this->getRow() == game->getBoardHeight() - 1 || this->getRow() == 0) {
		do {
			cout << "please choose a promotion: queen, knight, rook or bishop" << endl;
			cin >> input;
			trim(input);

			for (int i = 0; i < input.size(); i++) {//make sure this works
				tolower(input[i]);
			}
			if (input == "queen" || input == "knight" || input == "rook" || input == "bishop")
				validInput = true;

		} while (!validInput);

		char colorChar = this->getName()[0];
		string name;
		switch (input[0]) {
		case 'q':
			name = colorChar + (string)"Q";
			newPiece = new Queen(name, this->getIsBlack(), this->getRow(), this->getColumn());
			break;
		case 'r':
			name = colorChar + (string)"R";
			newPiece = new Rook(name, this->getIsBlack(), this->getRow(), this->getColumn());
			break;
		case 'k':
			name = colorChar + (string)"N";
			newPiece = new Knight(name, this->getIsBlack(), this->getRow(), this->getColumn());
			break;
		case 'b':
			name = colorChar + (string)"B";
			newPiece = new Bishop(name, this->getIsBlack(), this->getRow(), this->getColumn());
			break;
		
		default:
			cout << "never supposed to get here. promotion";
		}
		if (newPiece) {
			game->setSquareOnBoard(this->getRow(), this->getColumn(), newPiece);

			//delete this;//will this work .commiting suicide//I think it will work now because i deleted the copy. should not have mattered because it was a copy

		}

	}
}

ChessPiece* Pawn::copy() {
	return new Pawn(this->getName(), this->getIsBlack(), this->getRow(), this->getColumn());
}


