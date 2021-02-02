#include <iostream>
#include <string>
using namespace std;

enum Player {
	Human = -1,
	Blank = 0,
	Computer = 1
};

void printBoard(Player board[]);
Player checkWin(Player board[]);
void playGame(Player board[]);
int computerMove(Player board[]);
int humanMove(Player board[]);

int main() {
	char play = 'Y';

	while(play == 'Y') {
		Player board[9] = {Blank,Blank,Blank,Blank,Blank,Blank,Blank,Blank,Blank};
		printBoard(board);
		playGame(board);
		cout << "Do you want to play again? (Y/N) ";
		cin >> play;
		cout << endl;
	}
	return 0;
}

void playGame(Player board[]) {
	int numMoves = 0;
	while(true) {
		// get input from human and check win
		int hm = humanMove(board);
		while (hm == -1) {
			hm = humanMove(board);
		}
		board[hm] = Human;
		numMoves += 1;
		printBoard(board);
		cout << endl;
		if (checkWin(board) == Human) {
			cout << "You Win!" << endl;
			break;
		};
		if (numMoves == 5) {
			break;
		}
		// get choice from machine and check win
		int cm = computerMove(board);
		board[cm] = Computer;
		// leave loop if have a win
		printBoard(board);
		if (checkWin(board) == Computer) {
			cout << "Sorry, the Computer Has Win!" << endl;
			break;
		};
	}
	if (numMoves == 5)
	{
		cout << "It's a Draw!" << endl;
	}
}

int humanMove(Player board[]) {
	int humanMove;
	cout << "Where do you want to go? ";
	cin >> humanMove;
	if (board[humanMove - 1] == 0)
	{
		return humanMove - 1;
	} else {
		cout << "Invalid Move. Please choose again. ";
		return -1;
	}
}

Player checkWin(Player board[]) {
	Player winner;
	if (board[0] == -1 && board[1] == -1 && board[2] == -1) {
		winner = Human;
	}
	else if (board[3] == -1 && board[4] == -1 && board[5] == -1) {
		winner = Human;
	}
	else if (board[6] == -1 && board[7] == -1 && board[8] == -1) {
		winner = Human;
	}
	else if (board[0] == -1 && board[3] == -1 && board[6] == -1) {
		winner = Human;
	}
	else if (board[1] == -1 && board[4] == -1 && board[7] == -1) {
		winner = Human;
	}
	else if (board[2] == -1 && board[5] == -1 && board[8] == -1) {
		winner = Human;
	}
	else if (board[0] == -1 && board[4] == -1 && board[8] == -1) {
		winner = Human;
	}
	else if (board[2] == -1 && board[4] == -1 && board[6] == -1) {
		winner = Human;
	}
	else if (board[0] == 1 && board[1] == 1 && board[2] == 1) {
		winner = Computer;
	}
	else if (board[3] == 1 && board[4] == 1 && board[5] == 1) {
		winner = Computer;
	}
	else if (board[6] == 1 && board[7] == 1 && board[8] == 1) {
		winner = Computer;
	}
	else if (board[0] == 1 && board[3] == 1 && board[6] == 1) {
		winner = Computer;
	}
	else if (board[1] == 1 && board[4] == 1 && board[7] == 1) {
		winner = Computer;
	}
	else if (board[2] == 1 && board[5] == 1 && board[8] == 1) {
		winner = Computer;
	}
	else if (board[0] == 1 && board[4] == 1 && board[8] == 1) {
		winner = Computer;
	}
	else if (board[2] == 1 && board[4] == 1 && board[6] == 1) {
		winner = Computer;
	}
	else {
		winner = Blank;
	}
	return winner;
}

int computerMove(Player board[]) {
	int computersMove;
	//Check for 2 in a row
	for (int i = 1; i < 10; i++)
	{
		if (board[i-1] == 1) {
			if (board[i] == 1 && (i%3 - 1 == 0) && board[i+1] == 0)
			{
				return i+1;
			}
			else if (board[i+2] == 1 && (i<4) && board[i+5] == 0)
			{
				return i+5;
			}
			else if (i == 1 || i == 3 || i == 7 || i == 9)
				if (board[i-1] == 1 && board[4] == 1)
				{
					switch (i) {
						case 1:
							if (board[8] == 0)
							{
								return 8;
							}
							break;
						case 3:
							if (board[6] == 0)
							{
								return 6;
							}
							break;
						case 7:
							if (board[2] == 0)
							{
								return 2;
							}
							break;
						case 9:
							if (board[0] == 0)
							{
								return 0;
							}
							break;
						default:
							break;
					}
				}
		}
	}
	//Check for middle filled?
	if (board[4] == 0)
	{
		return 4;
	}
	//Check for opponent to have 2 in a row
	for (int i = 1; i < 10; i++)
	{
		if (board[i-1] == -1) {
			if (board[i] == -1 && (i%3 - 1 == 0) && board[i+1] == 0)
			{
				return i+1;
			}
			else if (board[i+2] == -1 && (i<4) && board[i+5] == 0)
			{
				return i+5;
			}
			else if (i == 1 || i == 3 || i == 7 || i == 9)
				if (board[i-1] == -1 && board[4] == -1)
				{
					switch (i) {
						case 1:
							if (board[8] == 0)
							{
								return 8;
							}
							break;
						case 3:
							if (board[6] == 0)
							{
								return 6;
							}
							break;
						case 7:
							if (board[2] == 0)
							{
								return 2;
							}
							break;
						case 9:
							if (board[0] == 0)
							{
								return 0;
							}
							break;
						default:
							break;
					}
				}
		}
	}
	//Go for two in a row
	for (int i = 1; i < 10; i++)
	{
		if (board[i-1] == 1 && board[i] == 0)
		{
			return i;
		}
	}

	//Go in corner
	for (int i = 1; i < 10; i++)
	{
		switch (i) {
			case 1:
				if (board[0] == 0)
					return 0;
				break;
			case 3:
				if (board[2] == 0)
					return 2;
				break;
			case 7:
				if (board[6] == 0)
					return 6;
				break;
			case 9:
				if (board[8] == 0)
					return 8;
				break;
			default:
				break;
		}
	}

	//Go on the side
	for (int i = 1; i < 10; i++)
	{
		switch (i) {
			case 2:
				if (board[1] == 0)
					return 1;
				break;
			case 4:
				if (board[3] == 0)
					return 3;
				break;
			case 6:
				if (board[5] == 0)
					return 5;
				break;
			case 8:
				if (board[7] == 0)
					return 7;
				break;
			default:
				break;
		}
	}

	return computersMove;
}

void printBoard(Player board[]) {

	for(int i = 0; i < 9; i++) {
		if((i == 2) || (i == 5) || (i == 8)) {
			if(board[i] == -1)
				cout << " X";
			else if (board[i] == 1)
				cout << " O";
			else
				cout << "  ";
		} else {
			if(board[i] == -1)
                                cout << "  X |";
                        else if (board[i] == 1)
                                cout << "  O |";
                        else
                                cout << "    |";
		}
		if(((i+1)%3 == 0) && (i != 8)) {
			cout << endl << "----|----|----" << endl;
		}
		if(i == 8)
			cout << endl;
	}

}
