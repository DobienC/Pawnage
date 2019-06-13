#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


char boardState[6][8];
int dataList[4];
int tempLocation[4];
int possibleMoves[192];
int possiblePlayerMoves[192];
int counter = 0;
int counterP = 0;
int maxDepth = 5;

// Prints the board
void printBoard(void) {
	int i = 0, j = 0;
	for (i = 0; i<6; i++) {
		for (j = 0; j<8; j++) {
			if (j <= 3) {
				if (boardState[i][j] == 'b') {
					boardState[i][j] = 'h';
				}
				else if (boardState[i][j] == 'B') {
					boardState[i][j] = 'H';
				}
			}
			else {
				if (boardState[i][j] == 'h') {
					boardState[i][j] = 'b';
				}
				else if (boardState[i][j] == 'H') {
					boardState[i][j] == 'B';
				}
			}
		}
	}
	printf("\n   ------------------------    COMPUTER\n");
	for (i = 5; i >= 0; i--) {
		printf(" %d ", i + 1);
		for (j = 0; j<8; j++) { printf(" %c ", boardState[i][j]); }
		printf("\n");
	}
	printf("   ------------------------    HUMAN\n");
	printf("    A  B  C  D  E  F  G  H\n");
	return;
}

// Updates Knight and Bishops if needed
void updatePieces() {
	int i = 0, j = 0;
	for (i = 0; i<6; i++) {
		for (j = 0; j<8; j++) {
			if (j <= 3) {
				if (boardState[i][j] == 'b') {
					boardState[i][j] = 'h';
				}
				else if (boardState[i][j] == 'B') { boardState[i][j] = 'H'; }
			}
			else {
				if (boardState[i][j] == 'h') {
					boardState[i][j] = 'b';
				}
				else if (boardState[i][j] == 'H') {
					boardState[i][j] == 'B';
				}
			}
		}
	}
}

// moves a piece in the game
void movePiece(int r1, int c1, int r2, int c2) {
	boardState[r2][c2] = boardState[r1][c1];
	boardState[r1][c1] = '-';
	updatePieces();
}

// Converts a character into an integer
int convertLetter(char c) {
	if (c == 'A' || c == 'a') {
		return 0;
	}
	else if (c == 'B' || c == 'b') {
		return 1;
	}
	else if (c == 'C' || c == 'c') {
		return 2;
	}
	else if (c == 'D' || c == 'd') {
		return 3;
	}
	else if (c == 'E' || c == 'e') {
		return 4;
	}
	else if (c == 'F' || c == 'f') {
		return 5;
	}
	else if (c == 'G' || c == 'g') {
		return 6;
	}
	else if (c == 'H' || c == 'h') {
		return 7;
	}
	else {
		return -1;
	}
}

// Converts the given integer into a character
char convertNumber(int n) {
	switch (n) {
	case 0:return 'A';
		break;
	case 1:return 'B';
		break;
	case 2:return 'C';
		break;
	case 3:return 'D';
		break;
	case 4:return 'E';
		break;
	case 5:return 'F';
		break;
	case 6:return 'G';
		break;
	case 7:return 'H';
		break;
	default:return 'N';
	}
}

// Checks if piece is a player piece
bool isPlayerPiece(char piece) {
	if (piece == 'p' || piece == 'b' || piece == 'h' || piece == 'k') {
		return true;
	}
	else { return false; }
}

// Checks if the piece is a computer piece
bool isComputerPiece(char piece) {
	if (piece == 'P' || piece == 'B' || piece == 'H' || piece == 'K') {
		return true;
	}
	else { return false; }
}

// This takes the possible moves for the computer and adds them to the possibleMoves array
void convertCompMoves(char col1, int row1, char col2, int row2) {
	possibleMoves[counter] = convertLetter(col1);
	counter++;
	possibleMoves[counter] = row1;
	counter++;
	possibleMoves[counter] = convertLetter(col2);
	counter++;
	possibleMoves[counter] = row2;
	counter++;
}

// This takes the possible moves for the player and adds them to the possiblePlayerMoves array
void convertPlayerMoves(char col1, int row1, char col2, int row2) {
	possiblePlayerMoves[counterP] = convertLetter(col1);
	counterP++;
	possiblePlayerMoves[counterP] = row1;
	counterP++;
	possiblePlayerMoves[counterP] = convertLetter(col2);
	counterP++;
	possiblePlayerMoves[counterP] = row2;
	counterP++;
}

void printMove(char col1, char row1, char col2, char row2) {
	convertCompMoves(col1, row1 - '0', col2, row2 - '0');
}

void printConsume(char col1, char row1, char col2, char row2) {
	convertCompMoves(col1, row1 - '0', col2, row2 - '0');
}

void printMoveP(char col1, char row1, char col2, char row2) {
	convertPlayerMoves(col1, row1 - '0', col2, row2 - '0');
}

void printConsumeP(char col1, char row1, char col2, char row2) {
	convertPlayerMoves(col1, row1 - '0', col2, row2 - '0');
}

// This finds all possible moves for a given computer piece
void getMoves(char piece, int col, int row) {
	if (piece == 'P') {// Pawn Moves
		if (isPlayerPiece(boardState[row - 1][col - 1])) {
			printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), (row)+'0');
		}
		if (isPlayerPiece(boardState[row - 1][col + 1])) {
			printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), (row)+'0');
		}
		if (boardState[row - 1][col] == '-') {
			printMove(convertNumber(col), (row + 1) + '0', convertNumber(col), (row)+'0');
		}
	}
	else if (piece == 'K') { // Kings Moves
		if (col >= 4) {
			if (isPlayerPiece(boardState[row][col + 1])) {
				printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), (row + 1) + '0');
			}
			if (boardState[row][col + 1] == '-') {
				printMove(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), (row + 1) + '0');
			}
		}
		else {
			if (boardState[row][col - 1] == '-') {
				printMove(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), (row + 1) + '0');
			}
			else if (isPlayerPiece(boardState[row][col - 1])) {
				printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), (row + 1) + '0');
			}
		}
	}
	else if (piece == 'B') {// Bishop Moves 
		int i = row + 1, j = col, k = col;
		for (i = row; i >= 0; i--) {
			if (k<0 && j >7) { i = -1; }
			if (k >= 0) {
				if (boardState[i][k] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(k), (i + 1) + '0');
				}
				else if (isComputerPiece(boardState[i][k])) {
					if (i != row) { k = -1; }
				}
				else if (isPlayerPiece(boardState[i][k])) {
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(k), (i + 1) + '0');
					k = -1;
				}k--;
			}
			if (j <= 7) {
				if (boardState[i][j] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(j), (i + 1) + '0');
				}
				else if (isComputerPiece(boardState[i][j])) {
					if (i != row) { j = 10; }
				}
				else if (isPlayerPiece(boardState[i][j])) {
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(j), (i + 1) + '0');
					j = 10;
				}j++;
			}
		}
		if (row <= 2) {
			i = row; j = col; k = col;
			for (i = row; i < 6; i++) {
				if (k<0 && j >7) { i = 7; }
				if (k >= 0) {
					if (isPlayerPiece(boardState[i][k])) {
						printConsume(convertNumber(col), (row + 1) + '0', convertNumber(k), (i + 1) + '0');
						k = -1;
					}
					else if (isComputerPiece(boardState[i][k])) {
						if (i != row) { k = -1; }
					}k--;
				}
				if (j <= 7) {
					if (isPlayerPiece(boardState[i][j])) {
						printConsume(convertNumber(col), (row + 1) + '0', convertNumber(j), (i + 1) + '0');
						j = 10;
					}
					else if (isComputerPiece(boardState[i][j])) {
						if (i != row) { j = 10; }
					}j++;
				}
			}
		}
	}
	else if (piece == 'H') {// Knight Pieces
		if (col - 2 >= 0) {
			if (row >= 2) {
				if (isPlayerPiece(boardState[row - 1][col - 2])) {// 7
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + '0');
				}
				else if (boardState[row - 1][col - 2] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + '0');
				}
				if (isPlayerPiece(boardState[row - 2][col - 1])) {// 6
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row - 1 + '0');
				}
				else if (boardState[row - 2][col - 1] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row - 1 + '0');
				}
			}
			else if (row >= 1) {
				if (isPlayerPiece(boardState[row - 1][col - 2])) {// 7
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + '0');
				}
				else if (boardState[row - 1][col - 2] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + '0');
				}
			}
			if (row <= 2) {// SENIOR
				if (isPlayerPiece(boardState[row + 1][col - 2])) {// 8
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + 2 + '0');
				}
				if (isPlayerPiece(boardState[row + 2][col - 1])) {// 1
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row + 3 + '0');
				}
			}
		}
		else if (col - 1 >= 0) {
			if (row >= 2) {
				if (isPlayerPiece(boardState[row - 2][col - 1])) {// 6
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row - 1 + '0');
				}
				else if (boardState[row - 2][col - 1] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row - 1 + '0');
				}
			}
			if (row <= 1) {// SENIOR
				if (isPlayerPiece(boardState[row + 2][col - 1])) {// 1
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row + 3 + '0');
				}
			}
		}

		if (col + 2 <= 7) {
			if (row >= 2) {
				if (isPlayerPiece(boardState[row - 1][col + 2])) {// 4
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + '0');
				}
				else if (boardState[row - 1][col + 2] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + '0');
				}
				if (isPlayerPiece(boardState[row - 2][col + 1])) {// 6
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row - 1 + '0');
				}
				else if (boardState[row - 2][col + 1] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row - 1 + '0');
				}
			}
			else if (row >= 1) {
				if (isPlayerPiece(boardState[row - 1][col + 2])) {// 4
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + '0');
				}
				else if (boardState[row - 1][col + 2] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + '0');
				}
			}
			if (row <= 2) {
				if (isPlayerPiece(boardState[row + 1][col + 2])) {//3
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + 2 + '0');
				}
				if (isPlayerPiece(boardState[row + 2][col + 1])) {// 2
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row + 3 + '0');
				}
			}
		}
		else if (col + 1 <= 7) {
			if (row >= 2) {
				if (isPlayerPiece(boardState[row - 2][col + 1])) {// 6
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row - 1 + '0');
				}
				else if (boardState[row - 2][col + 1] == '-') {
					printMove(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row - 1 + '0');
				}
			}
			if (row <= 2) {// SENIOR
				if (isPlayerPiece(boardState[row + 2][col + 1])) {// 2
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row + 3 + '0');
				}
			}
		}
	}
	else { printf("Non-Legal Moves\n"); }
}

// This finds all possible moves for given player piece
void getPlayerMoves(char piece, int col, int row) {
	if (piece == 'p') { // Pawn Moves
		if (boardState[row + 1][col] == '-') {
			printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col), (row + 2) + '0');
		}
		if (isComputerPiece(boardState[row + 1][col + 1])) {
			printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row + 2 + '0');
		}
		if (isComputerPiece(boardState[row + 1][col - 1])) {
			printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row + 2 + '0');
		}
	}
	else if (piece == 'k') { // Kings Moves
		if (col >= 4) {
			if (boardState[row][col + 1] == '-') {
				printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), (row + 1) + '0');
			}
			else if (isComputerPiece(boardState[row][col + 1])) {
				printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), (row + 1) + '0');
			}
		}
		else {
			if (boardState[row][col - 1] == '-') {
				printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), (row + 1) + '0');
			}
			else if (isComputerPiece(boardState[row][col - 1])) {
				printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), (row + 1) + '0');
			}
		}
	}
	else if (piece == 'b') { // Bishop Moves
		int i = row + 1, j = col, k = col;
		for (i = row; i<6; i++) {
			if (k<0 && j >7) { i = 6; }
			if (k >= 0) {
				if (boardState[i][k] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(k), (i + 1) + '0');
				}
				else if (isPlayerPiece(boardState[i][k])) {
					if (i != row) { k = -1; }
				}
				else if (isComputerPiece(boardState[i][k])) {
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(k), (i + 1) + '0');
					k = -1;
				}k--;
			}
			if (j <= 7) {
				if (boardState[i][j] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(j), (i + 1) + '0');
				}
				else if (isPlayerPiece(boardState[i][j])) {
					if (i != row) { j = 10; }
				}
				else if (isComputerPiece(boardState[i][j])) {
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(j), (i + 1) + '0');
					j = 10;
				}j++;
			}
		}
		if (row > 2) {
			i = row + 1; j = col + 1; k = col - 1;
			for (i = row; i >= 0; i--) {
				if (k<0 && j >7) { i = -1; }
				if (k >= 0) {
					if (isComputerPiece(boardState[i][k])) {
						printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(k), (i)+'0');
						k = -1;
					}
					else if (isPlayerPiece(boardState[i][k])) {
						if (i != row + 1) { k = -1; }
					}k--;
				}
				if (j <= 7) {
					if (isComputerPiece(boardState[i][j])) {
						printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(j), (i)+'0');
						j = 10;
					}
					else if (isPlayerPiece(boardState[i][j])) {
						if (i != row + 1) { j = 10; }
					} j++;
				}
			}
		}
	}
	else if (piece == 'h') { // Knight Moves
		if (col - 2 >= 0) {
			if (row <= 4) {
				if (isComputerPiece(boardState[row + 1][col - 2])) {// 8
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + 2 + '0');
				}
				else if (boardState[row + 1][col - 2] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + 2 + '0');
				}
				if (isComputerPiece(boardState[row + 2][col - 1])) {// 1
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row + 3 + '0');
				}
				else if (boardState[row + 2][col - 1] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row - 1 + '0');
				}
			}
			else if (row <= 5) {
				if (isPlayerPiece(boardState[row + 1][col - 2])) {// 8
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + 2 + '0');
				}
				else if (boardState[row + 1][col - 2] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + 2 + '0');
				}
			}
			if (row>2) {// SENIOR
				if (isComputerPiece(boardState[row - 1][col - 2])) {// 7
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col - 2), row + '0');
				}
				if (isComputerPiece(boardState[row - 2][col - 1])) {// 6
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row - 1 + '0');
				}
			}
		}
		else if (col - 1 >= 0) {
			if (row <= 5) {
				if (isComputerPiece(boardState[row + 2][col - 1])) {// 6
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row + 3 + '0');
				}
				else if (boardState[row + 2][col - 1] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row + 3 + '0');
				}
			}
			if (row>2) {// SENIOR
				if (isComputerPiece(boardState[row - 2][col - 1])) {// 1
					printConsume(convertNumber(col), (row + 1) + '0', convertNumber(col - 1), row - 1 + '0');
				}
			}
		}
		if (col + 2 <= 7) {
			if (row <= 4) {
				if (isComputerPiece(boardState[row + 1][col + 2])) {// 4
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + 2 + '0');
				}
				else if (boardState[row + 1][col + 2] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + 2 + '0');
				}
				if (isComputerPiece(boardState[row + 2][col + 1])) {// 6
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row + 3 + '0');
				}
				else if (boardState[row + 2][col + 1] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row + 3 + '0');
				}
			}
			else if (row >= 1) {
				if (isComputerPiece(boardState[row + 1][col + 2])) {// 4
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + 2 + '0');
				}
				else if (boardState[row + 1][col + 2] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + 2 + '0');
				}
			}
			if (row>2) {//SENIOR
				if (isComputerPiece(boardState[row - 1][col + 2])) {//3
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 2), row + '0');
				}
				if (isComputerPiece(boardState[row - 2][col + 1])) {// 2
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row - 1 + '0');
				}
			}
		}
		else if (col + 1 <= 7) {
			if (row <= 4) {
				if (isPlayerPiece(boardState[row + 2][col + 1])) {// 6
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row + 3 + '0');
				}
				else if (boardState[row + 2][col + 1] == '-') {
					printMoveP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row + 3 + '0');
				}
			}
			if (row>2) {// SENIOR
				if (isComputerPiece(boardState[row - 2][col + 1])) {// 2
					printConsumeP(convertNumber(col), (row + 1) + '0', convertNumber(col + 1), row - 1 + '0');
				}
			}
		}
	}
	else { printf("Non-Legal Moves\n"); }
}

// This evaluates all possible moves for each computer piece
void getComputerMoves() {
	int i = 0, j = 0;
	for (i = 0; i<6; i++) {
		for (j = 0; j<8; j++) {
			if (isComputerPiece(boardState[i][j])) {
				getMoves(boardState[i][j], j, i);
			}
		}
	}
}

// This evaluates all possible moves for each player piece
void makePlayerMoves() {
	int i = 0, j = 0;
	for (i = 0; i<6; i++) {
		for (j = 0; j<8; j++) {
			if (isPlayerPiece(boardState[i][j])) {
				getPlayerMoves(boardState[i][j], j, i);
			}
		}
	}
}

// This validates whether the user input is a valid move or not
bool isPossibleMove(int first, int second, int third, int fourth) {
	int numMoves = counterP + 1 / 4, moveIndex = 0, i = 0;
	for (i = 0; i < numMoves; i = i + 4) {
		if (possiblePlayerMoves[i] == first &&
			possiblePlayerMoves[i + 1] == second &&
			possiblePlayerMoves[i + 2] == third &&
			possiblePlayerMoves[i + 3] == fourth) {
			return true;
		}
	}
	return false;
}

// This gets the players inputs and stores them into the dataList for moving pieces
void getInputs() {
	char inputList[4];
	bool check = false;
	while (check == false) {
		printf("What is your move?\n");
		scanf("%s", inputList);
		if (isPossibleMove(convertLetter(inputList[0]), inputList[1] - '0', convertLetter(inputList[2]), inputList[3] - '0') == false) {
			printf("Invalid Move\n");
		}
		else { check = true; }
	}
	dataList[0] = inputList[1] - '1';
	dataList[1] = convertLetter(inputList[0]);
	dataList[2] = inputList[3] - '1';
	dataList[3] = convertLetter(inputList[2]);
	movePiece(dataList[0], dataList[1], dataList[2], dataList[3]);
}

// This prints out all computer moves
void printAllComputerMoves() {
	int numMoves = counter + 1 / 4;
	int moveIndex = 0;
	int i = 0;
	for (i = 0; i < numMoves; i = i + 4) {
		printf("Index %d: ", moveIndex);
		moveIndex++;
		printf("%c%c", convertNumber(possibleMoves[i]), possibleMoves[i + 1] + '0');
		printf("%c%c\n", convertNumber(possibleMoves[i + 2]), possibleMoves[i + 3] + '0');
	}
}

// This prints out all player moves
void printAllPlayerMoves() {
	int numMoves = counterP + 1 / 4;
	int moveIndex = 0;
	int i = 0;
	for (i = 0; i < numMoves; i = i + 4) {
		printf("Index %d: ", moveIndex);
		moveIndex++;
		printf("%c%c", convertNumber(possiblePlayerMoves[i]), possiblePlayerMoves[i + 1] + '0');
		printf("%c%c\n", convertNumber(possiblePlayerMoves[i + 2]), possiblePlayerMoves[i + 3] + '0');
	}
}

// This is the computers move generator
void computerMove() {
	int tempMoves[192];
	int i = 0, tempCounter = counter, depth = 0, best = -9999;
	int score, choice = 0;
	int oldRow, oldCol, newRow, newCol;
	char oldPiece, newPiece;
	for (i = 0; i< counter; i++) {
		tempMoves[i] = possibleMoves[i];
	}
	for (i = 0; i<tempCounter; i = i + 4) {
		oldRow = tempMoves[i + 1];
		oldCol = tempMoves[i];
		oldPiece = boardState[tempMoves[i + 1]][tempMoves[i]];
		newRow = tempMoves[i + 3];
		newCol = tempMoves[i + 2];
		newPiece = boardState[tempMoves[i + 3]][tempMoves[i + 2]];
		movePiece(tempMoves[i + 1], tempMoves[i], tempMoves[i + 3], tempMoves[i + 2]);
		updatePieces();
		score = min(depth + 1, best);
		if (score>best) {
			choice = i;
			best = score;
		}
		boardState[oldRow][oldCol] = oldPiece;
		boardState[newRow][newCol] = newPiece;
	}
	updatePieces();
	dataList[0] = tempMoves[choice + 1];
	dataList[1] = tempMoves[choice];
	dataList[2] = tempMoves[choice + 3];
	dataList[3] = tempMoves[choice + 2];

	printf("\nComputer Move: ");
	printf("%c%d%c%d ", convertNumber(dataList[1]), dataList[0], convertNumber(dataList[3]), dataList[2]);
	printf("(%c", convertNumber(dataList[1]));
	printf("%d", 7 - dataList[0]);
	printf("%c", convertNumber(dataList[3]));
	printf("%d)\n", 7 - dataList[2]);
	movePiece(dataList[0] - 1, dataList[1], dataList[2] - 1, dataList[3]);
	printBoard();
}

int min(int depth, int topBest) {
	int tempMoves[192];
	int i = 0, tempCounter, best = 9999, score = 0, choice = 0;
	int oldRow, oldCol, newRow, newCol;
	char oldPiece, newPiece;
	if (checkWinner() == 1000 || checkWinner() == -1000) {
		return checkWinner();
	}
	if (depth == maxDepth) {
		return evalBoard(depth);
	}
	counterP = 0;
	makePlayerMoves();
	tempCounter = counterP;
	for (i = 0; i< counterP; i++) {
		tempMoves[i] = possiblePlayerMoves[i];
	}
	for (i = 0; i<tempCounter; i = i + 4) {
		oldRow = tempMoves[i + 1];
		oldCol = tempMoves[i];
		oldPiece = boardState[tempMoves[i + 1]][tempMoves[i]];
		newRow = tempMoves[i + 3];
		newCol = tempMoves[i + 2];
		newPiece = boardState[tempMoves[i + 3]][tempMoves[i + 2]];
		movePiece(tempMoves[i + 1], tempMoves[i], tempMoves[i + 3], tempMoves[i + 2]);
		updatePieces();
		score = max(depth + 1, best);
		if (score<best) {
			best = score;
			if (best>topBest) {
				boardState[oldRow][oldCol] = oldPiece;
				boardState[newRow][newCol] = newPiece;
				return best;
			}
		}
		boardState[oldRow][oldCol] = oldPiece;
		boardState[newRow][newCol] = newPiece;
	}
	return best;
}

// Check scores and evaluation
// Min Max
int max(int depth, int topBest) {
	int tempMoves[192];
	int i = 0, tempCounter, best = -9999, score = 0, choice = 0;
	int oldRow, oldCol, newRow, newCol;
	char oldPiece, newPiece;
	if (checkWinner() == 1000 || checkWinner() == -1000) {
		return checkWinner();
	}
	if (depth == maxDepth) {
		return evalBoard(depth*-1);
	}
	counter = 0;
	getComputerMoves();
	tempCounter = counter;
	for (i = 0; i< counter; i++) {
		tempMoves[i] = possibleMoves[i];
	}
	for (i = 0; i<tempCounter; i = i + 4) {
		oldRow = tempMoves[i + 1];
		oldCol = tempMoves[i];
		oldPiece = boardState[tempMoves[i + 1]][tempMoves[i]];
		newRow = tempMoves[i + 3];
		newCol = tempMoves[i + 2];
		newPiece = boardState[tempMoves[i + 3]][tempMoves[i + 2]];
		movePiece(tempMoves[i + 1], tempMoves[i], tempMoves[i + 3], tempMoves[i + 2]);
		updatePieces();
		score = min(depth + 1, best);
		if (score>best) {
			best = score;
			if (best<topBest) {
				boardState[oldRow][oldCol] = oldPiece;
				boardState[newRow][newCol] = newPiece;
				return best;
			}
		}
		boardState[oldRow][oldCol] = oldPiece;
		boardState[newRow][newCol] = newPiece;
	}
	return best;
}

// This checks whether the player or computer has won the game
int checkWinner() {
	int i = 0, j = 0, playerKings = 0, computerKings = 0;
	for (i = 0; i<6; i++) {
		for (j = 0; j<8; j++) {
			if (boardState[i][j] == 'k') {
				playerKings++;
			}
			else if (boardState[i][j] == 'K') { computerKings++; }
		}
	}if (computerKings == 0) {
		return 1000;
	}
	else if (playerKings == 0) {
		return -1000;
	}
	else { return 0; }
}

// This evaluates the score at the given stage of the game
int evalBoard(int depth) {
	int i = 0, j = 0, playerKings = 0, computerKings = 0, playerBishops = 0, computerBishops = 0, playerKnights = 0, computerKnights = 0, playerPawns = 0, computerPawns = 0;
	int playerPieces = 0, computerPieces = 0;
	int score;
	updatePieces();
	for (i = 0; i<6; i++) {
		for (j = 0; j<8; j++) {
			if (boardState[i][j] == 'k') { playerKings++; }
			else if (boardState[i][j] == 'K') { computerKings++; }
			if (isPlayerPiece(boardState[i][j])) { playerPieces++; }
			else if (isComputerPiece(boardState[i][j])) { computerPieces++; }
			if (boardState[i][j] == 'p') { playerPawns++; }
			else if (boardState[i][j] == 'P') { computerPawns++; }
			if (boardState[i][j] == 'b') { playerBishops++; }
			else if (boardState[i][j] == 'B') { computerBishops++; }
			if (boardState[i][j] == 'h') { playerKnights++; }
			else if (boardState[i][j] == 'H') { computerKnights++; }
		}
	}
	score = score + (counterP + 1 / 4) - (counter + 1 / 4); // Evaluates the number of moves
	score = score + (playerKings * 1500) - (computerKings * 1500); // Evaluates the number of kings alive
	score = score + (playerPawns * 5) - (computerPawns * 5); // Evaluate the number of Pawns alive
	score = score + (playerBishops * 20) - (computerBishops * 20); // Evaluates the number of Bishops alive
	score = score + (playerKnights * 20) - (computerKnights * 20); // Evaluates the number of Knights alive
	return score + (depth * 100);
}

int main(void) {
	srand(time(NULL));
	int score = 0;
	initializeBoard();
	char firstMove = '0';
	printf("Who goes first?\n");
	printf("Input 1 for player. Input 2 for Computer\n");
	scanf("%d", &firstMove);
	printBoard();
	getComputerMoves();
	if (firstMove == 2) {
		makePlayerMoves();
		computerMove();
		counter = 0;
	}
	while (score != 1000 && score != -1000) {
		makePlayerMoves();
		getInputs();
		getComputerMoves();
		computerMove();
		if (checkWinner() == 0) {
			counter = 0;
			counterP = 0;
		}
		else {
			score = checkWinner();
			if (score == 1000) {
				printf("Player Wins!\n");
			}
			else { printf("Computer Wins!\n"); }
		}
	}
	return EXIT_SUCCESS;
}
