// Tic-Tac-Toe_Lib.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "Tic-Tac-Toe_Lib.h"

#define STRING_SIZE 50

// print board
void board(char square[][3])
{
	//system("cls");
	printf("\n\n   Tic Tac Toe   \n\n");

	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c  \n", square[0][0], square[0][1], square[0][2]);
	printf("_____|_____|_____\n");
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c  \n", square[1][0], square[1][1], square[1][2]);
	printf("_____|_____|_____\n");
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c  \n", square[2][0], square[2][1], square[2][2]);
	printf("     |     |     \n");
}

// checkWin return 1 if one wins, return -1 if draw, return if unfinish
int checkWin(char square[][3]) {
	int i;
	for (i = 0; i < 3; i++) {
		if (square[i][0] != ' ' && square[i][0] == square[i][1] && square[i][0] == square[i][2]) return 1;
		if (square[0][i] != ' ' && square[0][i] == square[1][i] && square[0][i] == square[2][i]) return 1;
	}
	if (square[0][0] != ' ' && square[0][0] == square[1][1] && square[0][0] == square[2][2]) return 1;
	if (square[2][0] != ' ' && square[2][0] == square[1][1] && square[2][0] == square[0][2]) return 1;
	int isDraw = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (square[i][j] == ' ') isDraw = 0;
		}
	}
	if (isDraw == 1) return -1;
	else return 0;
}

// write player steps to file
void writeToFile(FILE *fp, char square[][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (square[i][j] == ' ') fprintf(fp, "T ");
			else fprintf(fp, "%c ", square[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
}

// read player steps from file
void readFromFile(FILE * fp) {
	char c;
	while (!feof(fp)) {
		fscanf_s(fp, "%c", &c);
		printf("%c", c);
	}
}

// enter player name with number of players
void enterPlayerName(int num_players, char playerName[][STRING_SIZE]) {
	for (int i = 0; i < num_players; i++) {
		printf("Enter Player %d Name: ", i + 1);
		scanf_s("%s", playerName[i], STRING_SIZE);
		while ((getchar()) != '\n');
	}
}

// check mark position return true if right, return false if wrong
bool checkMarkPosition(int markAt) {
	if (markAt / 10 >= 1 && markAt / 10 <= 3 && markAt % 10 >= 1 && markAt % 10 <= 3) return true;
	else return false;
}

// check position is marked return true if it is marked, return false if not
bool isMark(int markAt, char square[][3]) {
	if (square[markAt / 10 - 1][markAt % 10 - 1] == ' ') return false;
	else return true;
}

// play game, print winner and save steps to file
void playGame(char playerName[][STRING_SIZE], FILE *savefile) {
	char square[3][3] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	board(square);
	int player = 1;
	char mark;
	int markAt = 0;
	while (checkWin(square) == 0) {
		player = (player % 2) ? 1 : 2;
		mark = (player == 1) ? 'X' : 'O';
		printf("\nYour turn %s - %c: ", playerName[player - 1], mark);
		scanf_s("%d", &markAt);
		if (checkMarkPosition(markAt)) {
			if (!isMark(markAt, square)) {
				square[markAt / 10 - 1][markAt % 10 - 1] = mark;
				player++;
			}
			else printf("Already marked - Remark!\n");
		}
		else printf("Invalid position - Remark!\n");
		board(square);
		writeToFile(savefile, square);
	}
	if (checkWin(square) == -1) printf("\nDRAW\n");
	else {
		printf("\nPlayer %d - %s win\n", player - 1, playerName[player - 1 - 1]);
	}
}
