#include "stdafx.h"
#include "chesspiece.h"

ChessPiece::ChessPiece(string name, bool isBlack, int row, int column) {
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