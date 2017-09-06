#include "stdafx.h"
#include <iostream>
#include "location.h"


Location::Location(int row, int column) {
	this->row = row;
	this->column = column;
	objectCounter++;
}

Location::Location(Location* baseLocation) {
	this->row = baseLocation->row;
	this->column = baseLocation->column;
}

int Location::getRow() {
	return row;
}
int Location::getColumn() {
	return column;
}

bool Location::operator==(Location& other) {
	if (this->getRow() == other.row && this->getColumn() == other.column)
		return true;
	else
		return false;
}