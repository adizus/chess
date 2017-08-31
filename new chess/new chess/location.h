#ifndef LOCATION
#define LOCATION

extern int objectCounter;

class Location {
	int row;
	int column;
public:
	Location(int r, int c);
	Location(Location*);
	int getRow();
	int getColumn();
	bool operator==(Location*);//location==location. make sure it works and is the right syntax;
};
#endif