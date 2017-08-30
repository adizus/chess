#include "stdafx.h"
#include "chesspiece.h"

ChessPiece::ChessPiece(string name,bool isBlack, int row,int column ) {
	this->isBlack = isBlack;
	this->name = name;
	this->row = row;
	this->column = column;
}

string ChessPiece::getName() {
	return name;
}
bool ChessPiece::getIsBlack() {
	return isBlack;
}

int ChessPiece::getColumn() {
	return column;
}

int ChessPiece::getRow() {
	return row;
}


void ChessPiece::setColumn(int column) {
	this->column = column;
}

void ChessPiece::setRow(int row) {
	this->row = row;
}

void ChessPiece::findPossibleMoves(Game * game) {
	possibleMoves.clear();
	for (int i = 0; i < game->getBoardWidth(); i++) {
		for (int j = 0; j < game->GetBoardHeight(); j++) {
			Location * possibleMove = new Location(i, j);
			if (isLegalMove(possibleMove,game))//make sure it gets to right object. should, because function is virtual
				possibleMoves.push_back(possibleMove);
		}
	}
}

vector<Location*> ChessPiece::getPossibleMovesVector() {
	return possibleMoves;
}

