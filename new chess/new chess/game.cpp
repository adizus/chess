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
int Game::GetBoardHeight() {
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


bool Game::isPossibleMove(ChessPiece*piece, Location* to, Location* from) {
	bool legalMove = true;
	if (!getPieceInLocation(from)) {
		cout << "there is no piece in that square" << endl;
		return false;
	}
	if (getPieceInLocation(from)->getIsBlack() && isWhiteTurn || !getPieceInLocation(from)->getIsBlack() && !isWhiteTurn) {
		cout << "it is not your turn" << endl;
		return false;
	}
	if (getPieceInLocation(to)) {
		if (getPieceInLocation(to)->getIsBlack() == piece->getIsBlack()) {//is endPlace occupied by a teammate
			cout << "you can't eat a team mate" << endl;
			return false;
		}
	}
	return true;

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

	for (int i = 0; i < input.size(); i++) { //maybe size_t instead of int.check why, and what is the difference
		tolower(input[i]);
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

void Game::executeMove(ChessPiece* mover, Location*to, Location*from, bool eating) {
	if (eating) {
		eat(getPieceInLocation(to));
	}
	setSquareOnBoard(to, mover);
	setSquareOnBoard(from, NULL);
	//this is not polymorphic
	if (mover->getName()[1] == 'P') {
		((Pawn*)mover)->setIsFirstMove(false);
		((Pawn*)mover)->checkAndExecutePawnPromotion(this);
		movesSinceLastPawnMovementOrLastEating = 0;
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

		do {
			string input = getUserInput();
			while (!checkUserInput(input))
				input = getUserInput();
			translateUserInput(input, &to, &from);//sending their addresses
			if (getPieceInLocation(from))
				movingPiece = getPieceInLocation(from);
		} while (!movingPiece);
		
		if (isPossibleMove(movingPiece, to, from)) {
			if (movingPiece->isLegalMove(to, this)) {
				if (getPieceInLocation(to))
					eating = true;
				
				Game* copyGame = new Game(this);
				ChessPiece* copyMover = copyGame->getPieceInLocation(from);
				copyGame->executeMove(copyMover, to, from, eating);
				if (copyGame->checkForCheck(!isWhiteTurn)) {
					delete copyGame;
					delete copyMover;
					cout << "that move puts your king in risk" << endl;
				}
				else {
					copyGame->changeTurn();
					if (copyGame->checkForCheck(isWhiteTurn)) {
						cout << "check" << endl;
						if (copyGame->checkForMate(isWhiteTurn)) {
							cout << "check-mate!" << endl;
							this->gameOver = true;
						}
					}
					delete copyGame;
					delete copyMover;
					movesSinceLastPawnMovementOrLastEating++;
					executeMove(movingPiece, to, from, eating);
					changeTurn();

				}
			}
			else if (checkAndExecuteIfCastling(to, from)) {
				movesSinceLastPawnMovementOrLastEating++;
				changeTurn();
			}
			else
				cout << "not legal move" << endl;
		}
		delete to;
		delete from;
		if (movingPiece)
			delete movingPiece;
		//	checkEndGame();//mate, draw... probably mate should be depended on check
	}
}

bool Game::checkAndExecuteIfCastling(Location *to, Location*from) {

	if (isWhiteTurn && from == whiteKingLocation && (to == new Location(7, 2) || to == new Location(7, 6)) ||//this may be very problematic. memoryleak
		!isWhiteTurn && from == blackKingLocation && (to == new Location(0, 2) || to == new Location(0, 6))) {//or overload operator

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
			if (squareRookHasToMoveThrough != NULL && getPieceInLocation(squareRookHasToMoveThrough) == NULL)//will this break
				if (getPieceInLocation(rookDestination) == NULL)
					if (!kingIsChecked)
						if (isSquareUnderAttack(rookDestination, !isWhiteTurn)) {
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
}


bool Game::checkForCheck(bool whiteMover) {
	vector<ChessPiece*> piecesVector = whiteMover ? whitePieces : blackPieces;
	Location* kingLocation = whiteMover ? blackKingLocation : whiteKingLocation;
	for (int i = 0; i < piecesVector.size(); i++) {
		if ((piecesVector[i])->isLegalMove(kingLocation, this)) {
			kingIsChecked = true;
			return true;
		}
	}
	kingIsChecked = false;
	return false;
}


bool Game::checkForMate(bool whiteMover) {//so the algorithem works but it couts everything on the way
	vector<ChessPiece*> piecesVector = whiteMover ? whitePieces : blackPieces;
	//add another copyboard
	for (int p = 0; p < piecesVector.size(); p++) {//for each piece I will go to each spot and then check if there is a check()
		for (int i = 0; i < boardWidth; i++) {
			for (int j = 0; j < boardHeight; j++) {
				ChessPiece * mover = piecesVector[p];
				Location* to = new Location(i, j);
				Location * from = new Location(mover->getRow(), mover->getColumn());
				bool eating = false;
				if (isPossibleMove(mover, to, from)) {
					if (piecesVector[p]->isLegalMove(to, this)) {
						if (getPieceInLocation(to))
							eating = true;
						executeMove(mover, to, from,eating);
						if (!checkForCheck(whiteMover))
							return false;
					}
				}
			}
		}
	}
	return true;
}

ChessPiece* Game::getPieceInLocation(Location* location) {
	return board[location->getRow()][location->getColumn()];//now very needed. but how?
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
	delete pieceBeingEaten;
	movesSinceLastPawnMovementOrLastEating = 0;
}
void Game::endGame() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			delete board[i][j];//need to check if ?
		}
	}
	delete blackKingLocation;
	delete whiteKingLocation;
}

