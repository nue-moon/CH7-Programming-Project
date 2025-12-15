#include <iostream>
#include <limits> // for numeric_limits
using namespace std;

const int SIZE = 3;
enum State { PLAY, X_WIN, O_WIN, TIE };

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '*';
}

void displayBoard(char board[SIZE][SIZE]) {
    cout << "\n   1 2 3\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i + 1 << "  ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void getLocation(int& row, int& col, char board[SIZE][SIZE]) {
    bool valid = false;
    while (!valid) {
        cout << "Enter row (1-3): ";
        if (!(cin >> row)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Enter column (1-3): ";
        if (!(cin >> col)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
            if (board[row - 1][col - 1] == '*') {
                valid = true;
            }
            else {
                cout << "Cell already taken. Try again.\n";
            }
        }
        else {
            cout << "Row and column must be between 1 and 3.\n";
        }
    }
}

void placeToken(char token, char board[SIZE][SIZE]) {
    int row, col;
    getLocation(row, col, board);
    board[row - 1][col - 1] = token;
}

bool checkForWinner(char token, char board[SIZE][SIZE]) {
    // Rows
    for (int i = 0; i < SIZE; i++)
        if (board[i][0] == token && board[i][1] == token && board[i][2] == token)
            return true;
    // Columns
    for (int j = 0; j < SIZE; j++)
        if (board[0][j] == token && board[1][j] == token && board[2][j] == token)
            return true;
    // Diagonals
    if (board[0][0] == token && board[1][1] == token && board[2][2] == token) return true;
    if (board[0][2] == token && board[1][1] == token && board[2][0] == token) return true;

    return false;
}

bool spaceLeft(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == '*') return true;
    return false;
}

State getBoardState(char token, char board[SIZE][SIZE]) {
    if (checkForWinner(token, board)) {
        return (token == 'X') ? X_WIN : O_WIN;
    }
    if (!spaceLeft(board)) return TIE;
    return PLAY;
}

int main() {
    char board[SIZE][SIZE];
    initializeBoard(board);
    displayBoard(board);

    State boardState = PLAY;
    char player1 = 'X', player2 = 'O';

    while (boardState == PLAY) {
        cout << "\nPlayer 1 (X):\n";
        placeToken(player1, board);
        displayBoard(board);
        boardState = getBoardState(player1, board);
        if (boardState != PLAY) break;

        cout << "\nPlayer 2 (O):\n";
        placeToken(player2, board);
        displayBoard(board);
        boardState = getBoardState(player2, board);
    }

    if (boardState == X_WIN) cout << "Player 1 wins!\n";
    else if (boardState == O_WIN) cout << "Player 2 wins!\n";
    else cout << "It's a tie!\n";

    return 0;
}