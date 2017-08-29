#ifndef GAME
#define GAME


#include <string>
#include <vector>
#include "chessPiece.h"
#include "location.h"

class ChessPiece;
class Location;
using namespace std;

class Game {
	bool isWhiteTurn = true;
	bool gameOver = false;

	vector < vector<ChessPiece*> > board;
	int boardWidth = 8;
	int boardHeight = 8;
	
	ChessPiece** blackPieces;
	ChessPiece** whitePieces;
	Location* blackKingLocation;
	Location* whiteKingLocation;


public:

	void play();
	void turn();
	void buildStandardBoard();
	void check();
	void mate();
	void switchTurn();
	void castling();
	bool isPossibleMove(ChessPiece*piece, Location*, Location *);
	void print();
	ChessPiece* getPieceInLocation(Location*);
	ChessPiece* getPieceInLocation(int row, int column);
	void executeMove(ChessPiece*, Location*, Location*, bool);
	string getUserInput();
	bool checkUserInput(string &input);
	void translateUserInput(string input, Location**, Location**); //findPlaceOnBoard
	int getBoardWidth();
	int GetBoardHeight();
	void setSquareOnBoard(Location*, ChessPiece*);
};
#endif 