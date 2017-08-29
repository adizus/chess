#include "stdafx.h"
#include <iostream>
#include "location.h"


Location::Location(int row, int column) {
	this->row = row;
	this->column = column;
}

int Location::getRow() {
	return row;
}
int Location::getColumn() {
	return column;
}

bool Location::operator==(Location* other) {
	if (this->getRow() == other->getRow() && this->getColumn() == other->getColumn())
		return true;
	else
		return false;
}