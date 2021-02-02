#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

struct gameCell {
  char state;
  vector<char> neighbors;
  int age;
};

void randomGame();
void customGame(string file);
void printBoard(vector<gameCell> &board);
void printHelp();
void setupGame(int &numSimulations);
void boardInitializer(vector<gameCell> &board, int &bsize, int &numSimulations);
void getNeighbors(vector<gameCell> &board, const int bsize);
void calculateNextGen(vector<gameCell> &board);

int main(int argc, char** argv)  {

  switch (argc) {
    case 1:
      randomGame();
      break;
    case 2:
      printHelp();
      break;
    case 3:
      if (strcmp(argv[1],"-f") == 0) {
        string filename = argv[2];
        customGame(filename);
      } else {
        printHelp();
      }
      break;
    default:
      printHelp();
  }

  return 0;
}

void randomGame() {
  srand(time(NULL));
  vector<gameCell> board;
  int boardSize;
  int numSims;
  boardInitializer(board, boardSize, numSims);
  cout << "\nPress any key to start the Simulation";
  cin.sync();
  cin.get();
  cout << "\nHere's the Colony " << endl;
  printBoard(board);
  cout << endl;
  for (int gen = 1; gen <= numSims; gen++) {
    getNeighbors(board, boardSize);
    calculateNextGen(board);
    cout << "\nHere's the Colony after Generation " << gen << endl;
    printBoard(board);
    cout << endl;
  }
}

void customGame(string file) {
  vector<gameCell> board;
  int boardSize;
  int numSims;
  ifstream inFile;
  inFile.open(file);
  char value;
  while(inFile.get(value)) {
    if (value == 'X' || value == '0') {
      gameCell newCell;
      newCell.state = value;
      newCell.age = 0;
      board.push_back(newCell);
    }
  }
  inFile.close();
  boardSize = board.size();
  setupGame(numSims);
  cout << "\nPress any key to start the Simulation";
  cin.sync();
  cin.get();
  cout << "\nHere's the Colony " << endl;
  printBoard(board);
  cout << endl;
  for (int gen = 1; gen <= numSims; gen++) {
    getNeighbors(board, boardSize);
    calculateNextGen(board);
    cout << "\nHere's the Colony after Generation " << gen << endl;
    printBoard(board);
    cout << endl;
  }
}

void printHelp() {
  cout << "Error: Input not recognized..." << endl;
  cout << "\nHow to use the Game of Life: " << endl;
  cout << "\tno flags : starts a game of a random colony with customizable options" << endl;
  cout << "\t-f <filename> : where <filename> is the file of the intial grid setup\n" << endl;
}

void printBoard(vector<gameCell> &board) {
  int size = sqrt(board.size());
  for (int j = 0; j < board.size(); j++) {
    if (j % size == 0) {
      cout << endl;
    }
    cout << board[j].state << " ";
  }
}

void setupGame(int &numSimulations) {
  cout << "\nWelcome to The Game of Life!" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "Each cell with one or no neighbors dies, as if by loneliness." << endl;
  cout << "Each cell with four or more neighbors dies, as if by overpopulation." << endl;
  cout << "Each cell with two or three neighbors survives." << endl;
  cout << "Each cell with three neighbors becomes populated." << endl;
  cout << "Each cell that ages over 10 generations dies." << endl;

  cout << "\nYour colony looks great! How many generations would you like to simulate? ";
  cin >> numSimulations;
  cin.ignore();
  cout << "\nFantastic! We're getting the simulation set up right now..." << endl;
}

void boardInitializer(vector<gameCell> &board, int &bsize, int &numSimulations) {

  int size = 20;
  cout << "\nWelcome to The Game of Life!" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "Each cell with one or no neighbors dies, as if by loneliness." << endl;
  cout << "Each cell with four or more neighbors dies, as if by overpopulation." << endl;
  cout << "Each cell with two or three neighbors survives." << endl;
  cout << "Each cell with three neighbors becomes populated." << endl;
  cout << "Each cell that ages over 10 generations dies." << endl;
  cout << "\nHow big would you like the population to be? (n x n sqaure, 10<= n <=50) n = ";
  cin >> size;
  cin.ignore();
  cout << "\nAwesome! How many generations would you like to simulate? (1<= x <=100): ";
  cin >> numSimulations;
  cin.ignore();
  cout << "\nFantastic! We're getting the Colony set up right now..." << endl;

  bsize = pow(size, 2);

  for (int i = 0; i < bsize; i++) {
    gameCell newCell;

    if ((rand() % 10) <= 7) {
      newCell.state = '0';
    } else {
      newCell.state = 'X';
    }
    newCell.age = 0;
    board.push_back(newCell);
  }
}

void getNeighbors(vector<gameCell> &board, const int bsize) {
  int size = sqrt(bsize);
  for (int i = 0; i < board.size(); i++) {
    vector<char> neigh(8,0);
    if (i == 0) {
      neigh[0] = board[1].state;
      neigh[1] = board[size].state;
      neigh[2] = board[size+1].state;
    }
    else if (i == (size - 1)) {
      neigh[0] = board[size-2].state;
      neigh[1] = board[2*size-2].state;
      neigh[2] = board[2*size-1].state;
    }
    else if (i == (bsize - 1)) {
      neigh[0] = board[size-2].state;
      neigh[1] = board[bsize-size-1].state;
      neigh[2] = board[bsize-size-2].state;
    }
    else if (i == (bsize - size)) {
      neigh[0] = board[bsize-size+1].state;
      neigh[1] = board[bsize-(2*size)].state;
      neigh[2] = board[bsize-(2*size)+1].state;
    }
    else if (i >= 1 && i <= (size - 2)) {
      neigh[0] = board[i+1].state;
      neigh[1] = board[i-1].state;
      neigh[2] = board[i+size-1].state;
      neigh[3] = board[i+size].state;
      neigh[4] = board[i+size+1].state;
    }
    else if (i >= (bsize - size + 1) && i <= (bsize-2)) {
      neigh[0] = board[i+1].state;
      neigh[1] = board[i-1].state;
      neigh[2] = board[i-size+1].state;
      neigh[3] = board[i-size].state;
      neigh[4] = board[i-size+1].state;
    }
    else if (i > 0 && (i % size == 0)) {
      neigh[0] = board[i+size].state;
      neigh[1] = board[i-size].state;
      neigh[2] = board[i+size+1].state;
      neigh[3] = board[i-size+1].state;
      neigh[4] = board[i+1].state;
    }
    else if (i > size - 1 && (i + 1) % size == 0) {
      neigh[0] = board[i+size].state;
      neigh[1] = board[i-size].state;
      neigh[2] = board[i+size-1].state;
      neigh[3] = board[i-size-1].state;
      neigh[4] = board[i-1].state;
    }
    else {
      neigh[0] = board[i+1].state;
      neigh[1] = board[i-1].state;
      neigh[2] = board[i+size-1].state;
      neigh[3] = board[i-size+1].state;
      neigh[4] = board[i+size].state;
      neigh[5] = board[i-size].state;
      neigh[6] = board[i+size+1].state;
      neigh[7] = board[i-size-1].state;
    }
    board[i].neighbors = neigh;
  }
}

void calculateNextGen(vector<gameCell> &board) {
  vector<gameCell> boardCopy = board;

  for (int i=0; i < board.size(); i++) {
    int liveNeighbors = 0;
    for (int j=0; j < board[i].neighbors.size(); j++) {
      if (board[i].neighbors[j] == 'X') {
        liveNeighbors++;
      }
    }
    if (liveNeighbors == 0 || liveNeighbors == 1 || liveNeighbors >= 4) {
        boardCopy[i].state = '0';
        boardCopy[i].age = 0;
    } else if (liveNeighbors == 2) {
        boardCopy[i] = board[i];
    } else if (liveNeighbors == 3) {
      if (boardCopy[i].state == '0') {
        boardCopy[i].state = 'X';
        boardCopy[i].age = 0;
      }
    }
    if (board[i].age == 9) {
      boardCopy[i].state = '0';
      boardCopy[i].age = 0;
    } else {
      boardCopy[i].age += 1;
    }
  }

  board = boardCopy;

}
