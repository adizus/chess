#include "stdafx.h"
#include "chessPiece.h"
#include "location.h "
#include "bishop.h"
#include "game.h"


bool Bishop::isLegalMove(Location* to, Game* game) {
	int rowDif, colDif;
	bool legalMove = false;

	for (int i = 1; i < 8 && !legalMove; i++) {//explain, don't hardcode

		if (to->getRow() + i == this->getRow() && to->getColumn() + i == this->getColumn() ||
			to->getRow() - i == this->getRow() && to->getColumn() - i == this->getColumn() ||
			to->getRow() - i == this->getRow() && to->getColumn() + i == this->getColumn() ||
			to->getRow() + i == this->getRow() && to->getColumn() - i == this->getColumn()
			) {

			legalMove = true;
			rowDif = to->getRow() - this->getRow();
			colDif = to->getColumn() - this->getColumn();

			if (rowDif < 0) {
				if (colDif == rowDif) {
					for (int r = -1, c = -1; r > rowDif && c > colDif && legalMove; r--, c--) {
						if (this->getRow() + r > -1 && this->getColumn() + c > -1) {
							if (game->getPieceInLocation(this->getRow() + r, this->getColumn() + c))
								legalMove = false;
						}
					}
				}
				else {
					for (int r = -1, c = 1; r > rowDif && c < colDif && legalMove; r--, c++) {
						if (this->getRow() + r > -1 && this->getColumn() + c > -1) {
							if (game->getPieceInLocation(this->getRow() + r, this->getColumn() + c))
								legalMove = false;
						}
					}
				}
			}
			else if (rowDif > 0) {
				if (colDif == rowDif) {
					for (int r = 1, c = 1; r < rowDif && c < colDif && legalMove; r++, c++) {
						if (this->getRow() + r > -1 && this->getColumn() + c > -1) {
							if (game->getPieceInLocation(this->getRow() + r, this->getColumn() + c))
								legalMove = false;
						}
					}
				}
				else {
					for (int r = 1, c = -1; r < rowDif && c > colDif && legalMove; r++, c--) {
						if (this->getRow() + r > -1 && this->getColumn() + c > -1) {
							if (game->getPieceInLocation(this->getRow() + r, this->getColumn() + c))
								legalMove = false;
						}
					}
				}
			}
			else
				cout << "never supposed to get here. bishop isLegalMove";
		}
	}
	return legalMove;
}

ChessPiece* Bishop::copy() {
	return new Bishop(this->name, this->isBlack, this->row, this->column);
}

