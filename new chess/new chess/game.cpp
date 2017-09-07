#include "stdafx.h"
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include "game.h"
#include "chessPiece.h"
#include "location.h"
#include "global.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"

using namespace std;

Game::Game() {
	objectCounter++;
}

int Game::getBoardWidth() {
	return boardWidth;
}
int Game::getBoardHeight() {
	return boardHeight;
}


void Game::buildStandardBoard() {


	vector <ChessPiece*> temp(boardHeight, NULL);
	vector < vector<ChessPiece*> > rows(boardWidth, temp);
	board = rows;

	vector <ChessPiece*> pieces(boardWidth * 2, NULL);
	whitePieces = blackPieces = pieces;
	//seems like there is a problem with pieces or something
	for (int i = 0; i < boardWidth; i++) {
		board[1][i] = new Pawn("BP", true, 1, i);
		blackPieces[i] = board[1][i];

		board[6][i] = new Pawn("WP", false, 6, i);
		whitePieces[i] = board[6][i];

		switch (i) {//this is hard coded
		case 0:
			board[0][i] = new Rook("BR", true, 0, i);
			blackPieces[i + boardWidth] = board[0][i];
			board[7][i] = new Rook("WR", false, 7, i);
			whitePieces[i + boardWidth] = board[7][i];
			board[0][i + 7] = new Rook("BR", true, 0, i + 7);
			blackPieces[i + 7 + boardWidth] = board[0][i + 7];
			board[7][i + 7] = new Rook("WR", false, 7, i + 7);
			whitePieces[i + 7 + boardWidth] = board[7][i + 7];
			break;
		case 1:
			board[0][i] = new Knight("BN", true, 0, i);
			blackPieces[i + boardWidth] = board[0][i];
			board[7][i] = new Knight("WN", false, 7, i);
			whitePieces[i + boardWidth] = board[7][i];
			board[0][i + 5] = new Knight("BN", true, 0, i + 5);
			blackPieces[i + 5 + boardWidth] = board[0][i + 5];
			board[7][i + 5] = new Knight("WN", false, 7, i + 5);
			whitePieces[i + 5 + boardWidth] = board[7][i + 5];
			break;
		case 2:
			board[0][i] = new Bishop("BB", true, 0, i);
			blackPieces[i + boardWidth] = board[0][i];
			board[7][i] = new Bishop("WB", false, 7, i);
			whitePieces[i + boardWidth] = board[7][i];
			board[0][i + 3] = new Bishop("BB", true, 0, i + 3);
			blackPieces[i + 3 + boardWidth] = board[0][i + 3];
			board[7][i + 3] = new Bishop("WB", false, 7, i + 3);
			whitePieces[i + 3 + boardWidth] = board[7][i + 3];
			break;
		case 3:
			board[0][i] = new Queen("BQ", true, 0, i);//make sure I didn't mix up king/queen places
			blackPieces[i + boardWidth] = board[0][i];
			board[7][i] = new Queen("WQ", false, 7, i);
			whitePieces[i + boardWidth] = board[7][i];
			break;
		case 4:
			board[0][i] = new King("BK", true, 0, i);
			blackPieces[i + boardWidth] = board[0][i];
			blackKingLocation = new Location(0, i);
			board[7][i] = new King("WK", false, 7, i);
			whitePieces[i + boardWidth] = board[7][i];
			whiteKingLocation = new Location(7, i);
			break;
		}
	}
}


string Game::isPossibleMove(ChessPiece*piece, Location* to, Location* from) {
	string message = "";
	bool legalMove = true;
	if (getPieceInLocation(from)==NULL) {
		message ="there is no piece in that square";
	}
	else if (getPieceInLocation(from)->getIsBlack() && isWhiteTurn || !getPieceInLocation(from)->getIsBlack() && !isWhiteTurn) {
		message = "it is not your turn";
		
	}
	else if (getPieceInLocation(to)) {
		if (getPieceInLocation(to)->getIsBlack() == piece->getIsBlack()) {//is endPlace occupied by a teammate
			message = "you can't eat a team mate" ;
		}
	}
	return message;

}


string Game::getUserInput() {
	string input;
	cin >> input;
	input = trim(input);
	return input;
}


bool Game::checkUserInput(string &input) {
	if (input.size() != 4) {
		cout << "input should have 4 characters";
		return false;
	}
	char c;
	for (int i = 0; i < input.size(); i++) { //maybe size_t instead of int.check why, and what is the difference
		input[i]=tolower(input[i]);
	}


	for (int i = 0; i < 4; i++) {
		char ch = input[i];
		if (i % 2 == 0) {
			switch (ch) {
			case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':
				continue;
			default: {
				cout << "please use only characters inside the range of the board, and in the right order: letter-number-letter-number\n";
				return false;
			}
			}
		}
		else {
			switch (ch) {
			case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':
				continue;
			default: {
				cout << "please use only characters inside the range of the board, and in the right order: letter-number-letter-number\n";
				return false;
			}
			}
		}
	}

	return true;
}


void Game::translateUserInput(string input, Location**to, Location**from) {//findPlaceOnBoard 
	int square;
	int beginRow, beginColumn, endRow, endColumn;
	for (int i = 0; i < 4; i++) {

		char ch = input[i];
		switch (ch) {
		case 'a':
		case '8':
			square = 0;
			break;
		case 'b':
		case '7':
			square = 1;
			break;
		case 'c':
		case '6':
			square = 2;
			break;
		case 'd':
		case '5':
			square = 3;
			break;
		case 'e':
		case '4':
			square = 4;
			break;
		case 'f':
		case '3':
			square = 5;
			break;
		case 'g':
		case '2':
			square = 6;
			break;
		case 'h':
		case '1':
			square = 7;
			break;
		}

		switch (i) {
		case 0:
			beginColumn = square;
			break;
		case 1:
			beginRow = square;
			break;
		case 2:
			endColumn = square;
			break;
		case 3:
			endRow = square;
		}
	}
	*from = new Location(beginRow, beginColumn);
	objectCounter++;
	*to = new Location(endRow, endColumn);
	objectCounter++;
}


void Game::print() {

	cout << (isWhiteTurn ? " white turn! " : " black turn! ") << endl;

	char letter = 97;
	cout << "  ";
	for (int i = 0; i < boardWidth; i++, letter++) {
		cout << "  " << letter << " ";
	}
	cout << endl;


	for (int i = 0; i < boardWidth; i++) {
		cout << endl;
		cout << boardWidth - i << "  ";
		for (int j = 0; j < boardHeight; j++) {

			cout << (board[i][j] ? " " + board[i][j]->getName() + " " : " // ");
		}

		cout << endl;

	}
}

void Game::executeMove(ChessPiece* mover, Location*to, Location*from, bool eating, bool realboard=true) {
	if ( nextMoveIsEnPassant) {
		executeEnPassant(mover, to, from);
		return;
	}

	if (eating) {
		eat(getPieceInLocation(to));
	}
	setSquareOnBoard(to, mover);
	setSquareOnBoard(from, NULL);
	//this is not polymorphic
	if (mover->getName()[1] == 'P') {
		((Pawn*)mover)->setIsFirstMove(false);
		if(realboard)
			((Pawn*)mover)->checkAndExecutePawnPromotion(this);
		movesSinceLastPawnMovementOrLastEating = -1;
	}

	else if (mover->getName()[1] == 'K') {
		((King*)mover)->setIsFirstMove(false);
		setKingLocation(mover);
	}

	else if (mover->getName()[1] == 'R') {
		((Rook*)mover)->setIsFirstMove(false);
	}
}

void Game::setSquareOnBoard(Location* location, ChessPiece* piece) {//
	if (piece) {
		board[location->getRow()][location->getColumn()] = piece;
		piece->setColumn(location->getColumn());
		piece->setRow(location->getRow());
	}
	else
		board[location->getRow()][location->getColumn()] = NULL;
}

void Game::setSquareOnBoard(int row, int column, ChessPiece* piece) {//
	if (piece) {
		board[row][column] = piece;
		piece->setColumn(column);
		piece->setRow(row);
	}
	else
		board[row][column] = NULL;
}


void Game::turn() {
	while (!gameOver) {
		print();
		Location*to = NULL;
		Location*from = NULL;
		ChessPiece* movingPiece = NULL;
		bool eating = false;
		
		string input = getUserInput();
		while (!checkUserInput(input))
			input = getUserInput();
		translateUserInput(input, &to, &from);//sending their addresses
		
		string message = checkMove(to, from);
		if (message != "") {
			cout << message << endl;
		}
			else {
				movingPiece = getPieceInLocation(from);
				eating = getPieceInLocation(to);
				executeMove(movingPiece, to, from, eating);
				afterMove();
			}
		delete to;
		delete from;
		//if (movingPiece)
		//	delete movingPiece;
		//	checkEndGame();//mate, draw... probably mate should be depended on check
	}
	endGame();
}

bool Game::checkAndExecuteIfCastling(Location *to, Location*from) {
	Location* whiteOption1 = new Location(7, 2);
	Location* whiteOption2 = new Location(7, 6);
	Location* blackOption1 = new Location(0, 2);
	Location* blackOption2 = new Location(0, 6);
	if (isWhiteTurn && *from == *whiteKingLocation && (*to == *whiteOption1 || *to == *whiteOption2) ||
		!isWhiteTurn && *from == *blackKingLocation && (*to == *blackOption1 || *to == *blackOption2)) {

		King * king = (King*)getPieceInLocation(from);
		Rook*rook;
		Location *rookDestination;
		Location * squareRookHasToMoveThrough = NULL;

		if (isWhiteTurn) {
			if (to == new Location(7, 2)) {
				rook = (Rook*)getPieceInLocation(7, 0);
				rookDestination = new Location(7, 3);
				squareRookHasToMoveThrough = new Location(7, 1);
			}
			else {
				rook = (Rook*)getPieceInLocation(7, 7);
				rookDestination = new Location(7, 5);
			}
		}
		else {
			if (to == new Location(0, 2)) {
				rook = (Rook*)getPieceInLocation(0, 0);
				rookDestination = new Location(0, 3);
				squareRookHasToMoveThrough = new Location(0, 1);
			}
			else {
				rook = (Rook*)getPieceInLocation(0, 7);
				rookDestination = new Location(0, 5);
			}
		}
		if (king->getIsFirstMove() && rook->getIsFirstMove()) {
			if (squareRookHasToMoveThrough == NULL || getPieceInLocation(squareRookHasToMoveThrough) == NULL)//will this break
				if (getPieceInLocation(rookDestination) == NULL)
					if (!kingIsChecked)
						if (!isSquareUnderAttack(rookDestination, !isWhiteTurn)) {
							executeCastling(king, rook, to, from, rookDestination);
							return true;
						}

		}
	}
	return false;
}

bool Game::isSquareUnderAttack(Location* location, bool whiteMover) {
	vector<ChessPiece*> piecesVector = whiteMover ? whitePieces : blackPieces;
	for (int i = 0; i < piecesVector.size(); i++) {
		if ((piecesVector[i])->isLegalMove(location, this)) {
			return true;
		}
	}
	return false;
}

void Game::executeCastling(ChessPiece*king, ChessPiece*rook, Location *to, Location*from, Location* rooksDestination) {
	int rookFromRow = rook->getRow();
	int rookFromColumn = rook->getColumn();

	setSquareOnBoard(to, king);
	setSquareOnBoard(rooksDestination, rook);
	setSquareOnBoard(from, NULL);
	setSquareOnBoard(rookFromRow, rookFromColumn, NULL);

	movesSinceLastPawnMovementOrLastEating++;
	changeTurn();
}


bool Game::checkForCheck(bool whiteMover) {
	vector<ChessPiece*> piecesVector = whiteMover ? whitePieces : blackPieces;
	Location* kingLocation = whiteMover ? blackKingLocation : whiteKingLocation;
	for (int i = 0; i < piecesVector.size(); i++) {
		if (piecesVector[i]) {
			if ((piecesVector[i])->isLegalMove(kingLocation, this)) {
				return true;
			}
		}
	}
	return false;
}


bool Game::checkForMate(bool whiteMover) {//so the algorithem works but it couts everything on the way

	vector<ChessPiece*> piecesVector;
	Game* copyGame = NULL;

	for (int p = 0; p < (whiteMover ? whitePieces.size() : blackPieces.size()); p++) {//for each piece I will go to each spot and then check if there is a check()
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				if (copyGame == NULL) {
					copyGame = new Game(this);
					piecesVector = whiteMover ? copyGame->whitePieces : copyGame->blackPieces;
				}
				ChessPiece * mover = piecesVector[p];
				Location* to = new Location(i, j);
				Location * from = new Location(mover->getRow(), mover->getColumn());
				bool eating = false;
				if (isPossibleMove(mover, to, from) == "") {
					if (piecesVector[p]->isLegalMove(to, this)) {
						if (getPieceInLocation(to))
							eating = true;
						copyGame->executeMove(mover, to, from, eating,false);
						copyGame->changeTurn();
						if (!checkForCheck(whiteMover)) {
							delete copyGame;
							copyGame = NULL;
							delete to;
							delete from;
							return false;
						}
						else {
							delete copyGame;
							copyGame = NULL;
						}
					}
				}
				delete to;
				delete from;
			}
		}
	}
	gameOver = true;
	return true;
}



ChessPiece* Game::getPieceInLocation(Location* location) {
	return board[location->getRow()][location->getColumn()];
}

ChessPiece* Game::getPieceInLocation(int row, int column) {
	return board[row][column];
}

void Game::play() {
	buildStandardBoard();
	turn();
}

Game::Game(Game* baseGame) {
	this->isWhiteTurn = baseGame->isWhiteTurn;
	this->gameOver = baseGame->gameOver;
	this->boardHeight = baseGame->boardHeight;
	this->boardWidth = baseGame->boardWidth;
	this->movesSinceLastPawnMovementOrLastEating = baseGame->movesSinceLastPawnMovementOrLastEating;

	vector <ChessPiece*>temp(this->boardHeight, NULL);
	vector< vector <ChessPiece*> > rows(this->boardWidth, temp);
	this->board = rows;

	for (int i = 0; i < this->boardHeight; i++) {
		for (int j = 0; j < this->boardWidth; j++) {
			if (baseGame->board[i][j]) {
				this->board[i][j] = baseGame->board[i][j]->copy();
				this->board[i][j]->getIsBlack() ? this->blackPieces.push_back(this->board[i][j]) : this->whitePieces.push_back(this->board[i][j]);
			}
		}
	}

	this->blackKingLocation = new Location(baseGame->blackKingLocation);
	this->whiteKingLocation = new Location(baseGame->whiteKingLocation);

}

void Game::changeTurn() {
	isWhiteTurn = !isWhiteTurn;
}

void Game::setKingLocation(ChessPiece*king) {
	(king->getIsBlack() ? blackKingLocation : whiteKingLocation) = new Location(king->getRow(), king->getColumn());
}

void Game::eat(ChessPiece* pieceBeingEaten) {
	
	bool isBlack = pieceBeingEaten->getIsBlack();
	int row = pieceBeingEaten->getRow();
	int column = pieceBeingEaten->getColumn();
	vector<ChessPiece*> piecesVector = isBlack ? blackPieces : whitePieces;
	int placeInPiecesVector;

	for (int i = 0; i <piecesVector.size(); i++){
		if (piecesVector[i] == pieceBeingEaten) {
			placeInPiecesVector = i;
			break;
		}
	}
	board[row][column] = NULL;
	(isBlack ? blackPieces[placeInPiecesVector] : whitePieces[placeInPiecesVector]) = NULL;
	delete pieceBeingEaten;
	movesSinceLastPawnMovementOrLastEating = -1;
}

void Game::endGame() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			delete board[i][j];//need to check if ?
		}
	}
	delete blackKingLocation;
	delete whiteKingLocation;
	cout << endl << "game over!" << endl;	
}

string Game::checkMove(Location * to, Location* from) {
	string message="";
	bool eating = false;
	ChessPiece*movingPiece = getPieceInLocation(from);
	message = isPossibleMove(movingPiece, to, from);
	if (message != "") {
		return message;
	}
	if (!movingPiece->isLegalMove(to, this)) {
		if (checkAndExecuteIfCastling(to, from))//i dont like this. can be changed
			message = "castled successfully";
		else
			message = "not legal move";
	}
	if (message != "")
		return message;
	message = checkMoveByCopying(to, from);
	return message;
}
string Game::checkMoveByCopying(Location * to, Location * from) {
	
	string message = "";
	bool eating = false;
	if (getPieceInLocation(to))
		eating = true;

	Game* copyGame = new Game(this);
	ChessPiece* copyMover = copyGame->getPieceInLocation(from);
	copyGame->executeMove(copyMover, to, from, eating, false);
	if (copyGame->checkForCheck(!isWhiteTurn)) {
		delete copyGame;
		//delete copyMover;
		message = "that move puts your king in risk";
	}
	return message;
}

void Game::afterMove() {
	bool noPossibleMoves = false;
	Location* saveEnPassantLocation = NULL;
	if(enPassantLocation)
		saveEnPassantLocation = new Location(enPassantLocation->getRow(), enPassantLocation->getColumn());
	if (checkForCheck(isWhiteTurn)) {
		kingIsChecked = true;
	}
	else
		kingIsChecked = false;
	if (checkForMate(isWhiteTurn)) {
		noPossibleMoves = true;
	}
	if (noPossibleMoves && kingIsChecked) {
		cout << "check-mate!" << endl;
		gameOver = true;
	}
	if (noPossibleMoves && !kingIsChecked) {
		cout << "stale mate" << endl;
		gameOver = true;
	}
	if (!noPossibleMoves&&kingIsChecked)
		cout << "check!" << endl;
	
	changeTurn();
	movesSinceLastPawnMovementOrLastEating++;

	if (movesSinceLastPawnMovementOrLastEating >= 50) {
		cout << "50 moves rule" << endl;
		gameOver = true;
	}
	if (compareAndSaveLastBoardOrThreefoldRepitionEndGame()) {
		cout << "Threefold Repition. game over" << endl;
		gameOver = true;
	}
	enPassantLocation = saveEnPassantLocation;
}

bool Game::compareAndSaveLastBoardOrThreefoldRepitionEndGame() {
	static bool firstTime = true;
	static int numOfMoves = 0;
	numOfMoves++;

	if (firstTime) {
		vector <ChessPiece*> temp(boardHeight, NULL);
		vector < vector<ChessPiece*> > rows(boardWidth, temp);
		lastBoard = rows;
		firstTime = false;
		return false;
	}
	if (numOfMoves % 4 == 0) {
		if (boardsAreIdentical(board, lastBoard)) {
			if (twoBoardRepitition == true)
				return true;
			else
				twoBoardRepitition = true;
		}
		else {
			lastBoard = copyBoard();
			twoBoardRepitition = false;
		}
	}
	return false;
}

bool Game::boardsAreIdentical(vector < vector<ChessPiece*> > board, vector < vector<ChessPiece*> > lastBoard) {
	bool identical = true;
	for (int i = 0; i < boardHeight&& identical; i++) {
		for (int j = 0; j < boardWidth && identical; j++) {
			if (board[i][j] && lastBoard[i][j]) {
				if (board[i][j]->getName() != lastBoard[i][j]->getName())
					identical = false;
			}
			else if (!board[i][j] && lastBoard[i][j] || board[i][j] && !lastBoard[i][j]) {
				identical = false;
			}
		}
	}
	return identical;
}

vector < vector<ChessPiece*> > Game::copyBoard() {
	vector < vector<ChessPiece*> > copyBoard;
	
	vector <ChessPiece*>temp(this->boardHeight, NULL);
	vector< vector <ChessPiece*> > rows(this->boardWidth, temp);
	copyBoard = rows;

	for (int i = 0; i < this->boardHeight; i++) {
		for (int j = 0; j < this->boardWidth; j++) {
			if (this->board[i][j]) 
				copyBoard[i][j] = this->board[i][j]->copy();
		}
	}
	return copyBoard;
}

Location * Game::getEnPassantLocation() {
	return enPassantLocation;
}

void Game::setEnPassantLocation(int row, int column) {
	enPassantLocation = new Location(row, column);
}
void Game::setEnPassantLocation() {
	delete enPassantLocation;
	enPassantLocation = NULL;
}
void Game::executeEnPassant(ChessPiece* mover, Location*to,Location * from) {
	eat(lastPawnToMove);
	setSquareOnBoard(to, mover);
	setSquareOnBoard(from, NULL);
}

void Game::setLastPawnToMove(ChessPiece* pawn) {
	lastPawnToMove = pawn;
}

ChessPiece* Game::getLastPawnToMove() {
	return lastPawnToMove;
}
	
void Game::setNextMoveIsEnPassant(bool nextMoveIsEnPassant) {
	this->nextMoveIsEnPassant = nextMoveIsEnPassant;
}

bool Game::getNextMoveIsEnPassant() {
	return nextMoveIsEnPassant;
}

vector<ChessPiece*> Game::getPiecesVector(bool askForBlackPieces) {
	return askForBlackPieces ? blackPieces : whitePieces;
}
void Game::setPiecesVector(bool setBlackPieces, int index,  ChessPiece* piece) {
	setBlackPieces ? blackPieces[index] : whitePieces[index] = piece;
}