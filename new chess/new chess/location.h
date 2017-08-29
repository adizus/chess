#ifndef LOCATION
#define LOCATION

class Location {
	int row;
	int column;
public:
	Location(int r, int c);
	int getRow();
	int getColumn();
	bool operator==(Location*);//location==location. make sure it works and is the right syntax;
};
#endif