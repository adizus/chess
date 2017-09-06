#ifndef GAME
#define GAME

#include <string>
#include <vector>
#include "chessPiece.h"
#include "location.h"

class ChessPiece;
class Location;
using namespace std;
extern int objectCounter;

class Game {
	bool isWhiteTurn = true;
	bool gameOver = false;

	vector < vector<ChessPiece*> > board;
	int boardWidth = 8;
	int boardHeight = 8;
	vector<ChessPiece*> blackPieces;
	vector<ChessPiece*> whitePieces;
	//ChessPiece** blackPieces;
	//ChessPiece** whitePieces;
	Location* blackKingLocation;
	Location* whiteKingLocation;
	bool kingIsChecked;
	int movesSinceLastPawnMovementOrLastEating = 0;
	vector <vector<ChessPiece*> > lastBoard;
	bool twoBoardRepitition=false;
public:
	Game();
	Game(Game*);
	void play();
	void turn();
	void buildStandardBoard();
	bool checkForCheck(bool whiteMover);
	bool checkAndExecuteIfCastling(Location*, Location*);
	string isPossibleMove(ChessPiece*piece, Location*, Location *);
	void print();
	ChessPiece* getPieceInLocation(Location*);
	ChessPiece* getPieceInLocation(int row, int column);
	void executeMove(ChessPiece*, Location*, Location*, bool);
	string getUserInput();
	bool checkUserInput(string &input);
	void translateUserInput(string input, Location**, Location**); //findPlaceOnBoard
	int getBoardWidth();
	int getBoardHeight();
	void setSquareOnBoard(Location*, ChessPiece*);
	void setSquareOnBoard(int row, int column, ChessPiece*);
	bool checkForMate(bool);
	void changeTurn();
	bool isSquareUnderAttack(Location*, bool);
	void executeCastling(ChessPiece*, ChessPiece*, Location*, Location*, Location*);
	void setKingLocation(ChessPiece*);
	void eat(ChessPiece*);
	void endGame();
	string checkMove(Location*, Location*);
	string checkMoveByCopying(Location*,Location*);
	void afterMove();
	void compareAndSaveLastBoard();
	bool boardsAreIdentical(vector < vector<ChessPiece*> >, vector < vector<ChessPiece*> >);
	vector < vector<ChessPiece*> > copyBoard();
};
#endif 