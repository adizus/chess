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

void Pawn::promotePawn(Game* game) {
	bool getInput=false;
	string input;
	ChessPiece* newPiece=NULL;
	if (this->getRow() == game->GetBoardHeight() || this->getRow() == 0) {
		do {
			cout << "please choose a promotion: queen, knight, rook or bishop" << endl;
			cin >> input;
			trim(input);

			for (int i = 0; i < input.size(); i++) {//make sure this works
				tolower(input[i]);
			}
			if (input == "queen" || input == "knight" || input == "rook" || input == "bishop")
				getInput = true;

		} while (!getInput);

		char nameChar = this->name[0];
		switch (input[0]) {
		case 'q':
			newPiece = new Queen(nameChar + "Q", this->isBlack, this->row, this->column);
			break;
		case 'r':
			newPiece = new Rook(nameChar + "R", this->isBlack, this->row, this->column);
			break;
		case 'b':
			newPiece = new Bishop(nameChar + "B", this->isBlack, this->row, this->column);
			break;
		case 'k':
			newPiece = new Knight(nameChar + "N", this->isBlack, this->row, this->column);
			break;
		default:
			cout << "never supposed to get here. promotion";
		}
		if (newPiece) {
			game->setSquareOnBoard(this->getRow(), this->getColumn(), newPiece);
		
			delete this;//will this work .commiting suicide

		}
		
	}
}

ChessPiece* Pawn::copy() {
	return new Pawn(this->name, this->isBlack, this->row, this->column);
}




