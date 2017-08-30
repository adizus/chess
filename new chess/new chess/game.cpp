#include "stdafx.h"
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include "game.h"
#include "chessPiece.h"
#include "pawn.h"
#include "location.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"

using namespace std;

int Game::getBoardWidth() {
	return boardWidth;
}
int Game::GetBoardHeight() {
	return boardHeight;
}

//Location* Game::getLocation(int row, int column) {
//	return board[row][column];
//}


void Game::buildStandardBoard() {

	//cout <<"building "<< (isWhiteTurn ? " white turn! " : " black turn! ") << endl;
	vector <ChessPiece*> temp(boardHeight, NULL);
	vector < vector<ChessPiece*> > rows(boardWidth, temp);
	board = rows;

	blackPieces = new ChessPiece*[boardWidth * 2];
	whitePieces = new ChessPiece*[boardWidth * 2];

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
			break;
		case 1:
			board[0][i] = new Knight("BN", true, 0, i);
			blackPieces[i + boardWidth] = board[0][i];
			board[7][i] = new Knight("WN", false, 7, i);
			whitePieces[i + boardWidth] = board[7][i];
			break;
		case 2:
			board[0][i] = new Bishop("BB", true, 0, i);
			blackPieces[i + boardWidth] = board[0][i];
			board[7][i] = new Bishop("WB", false, 7, i);
			whitePieces[i + boardWidth] = board[7][i];
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

string trim(string input) {//can it be added to string itself?
	int inputLength = input.size();
	int begin = input.find_first_not_of(" ");
	int end = input.find_last_not_of(" ");
	string newInput = input.substr(begin, end - begin - 1);
	return input;//maybe use reference
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

	//transform(input.begin(), input.end(), input.begin(), ::tolower);//same as next row.ask about syntax

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
	*to = new Location(endRow, endColumn);
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

/*
string operator+(string str, int i) {//make sure this works how I expect it to, and check if it is needed
return str + (char*)i;
}*/

void Game::executeMove(ChessPiece* mover, Location*to, Location*from, bool eating = false) {
	
	setSquareOnBoard(to, mover);
	setSquareOnBoard(from, NULL);
	
	if (mover->getName()[1] == 'P') {
		dynamic_cast<Pawn*>(mover)->setIsFirstMove(false);
	}

	if (mover->getName()[1] == 'K') {
		dynamic_cast<King*>(mover)->setIsFirstMove(false);
	}

	if (mover->getName()[1] == 'R') {
		dynamic_cast<Rook*>(mover)->setIsFirstMove(false);
	}

	isWhiteTurn = !isWhiteTurn;
	/*if (eating) {
	eat();
	}*/
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


void Game::turn() {
	while (!gameOver) {
		print();
		Location*to = NULL;
		Location*from = NULL;
		ChessPiece* movingPiece = NULL;

		do {
			string input = getUserInput();
			while (!checkUserInput(input))
				input = getUserInput();
			translateUserInput(input, &to, &from);//sending their addresses
			if (getPieceInLocation(from))
				movingPiece = getPieceInLocation(from);
		} while (!movingPiece);

		if (isPossibleMove(movingPiece, to, from)) {
			if (movingPiece->isLegalMove(to, this))
				executeMove(movingPiece, to, from);
			else
				cout << "not legal move" << endl;
		}
		gatherAllPossibleMoves();
		checkForCheck();

		//	checkEndGame();//mate, draw... maybe mate should be depended on check




	}
}
void Game::gatherAllPossibleMoves(bool whiteMover) {
	vector<ChessPiece*> piecesVector = whiteMover ? whitePieces : blackPieces;
	allPossibleMovesForNextTurn.clear();
	for (int i = 0; i < piecesVector.size(); i++) {
		piecesVector[i]->findPossibleMoves(this);
		allPossibleMovesForNextTurn.insert(allPossibleMovesForNextTurn.end(), piecesVector[i]->getPossibleMovesVector.begin(), piecesVector[i]->getPossibleMovesVector.end());
	}
}

bool Game::checkForCheck(bool whiteMover) {
	for (int i = 0; i < allPossibleMovesForNextTurn.size(); i++) {
		if (allPossibleMovesForNextTurn[i] == (whiteMover ? blackKingLocation : whiteKingLocation))
			return true;
	}
	return false;
}

bool Game::checkForMate() {

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
