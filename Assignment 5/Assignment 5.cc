#include <iostream>
#include <limits>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE] = { {'_', '_', '_'},
                           {'_', '_', '_'},
                           {'_', '_', '_'} };

// Function to print the board
void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

// Check if there are moves left
bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

// Evaluate board state
int evaluate() {
    // Rows
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == 'X') return +10;
            if (board[row][0] == 'O') return -10;
        }
    }

    // Columns
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == 'X') return +10;
            if (board[0][col] == 'O') return -10;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] && 
        board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') return +10;
        if (board[0][0] == 'O') return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') return +10;
        if (board[0][2] == 'O') return -10;
    }

    return 0; // No winner
}

// Minimax function
int minimax(bool isMax) {
    int score = evaluate();

    // If Maximizer has won
    if (score == 10) return score;

    // If Minimizer has won
    if (score == -10) return score;

    // If no moves left => draw
    if (!isMovesLeft()) return 0;

    // Maximizer's move (X)
    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'X';
                    best = max(best, minimax(false));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    // Minimizer's move (O)
    else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'O';
                    best = min(best, minimax(true));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

// Find best move for X
pair<int, int> findBestMove() {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '_') {
                board[i][j] = 'X';
                int moveVal = minimax(false);
                board[i][j] = '_';
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    cout << "Initial Tic-Tac-Toe Board:\n";
    printBoard();

    // Example: user plays O at (1,1)
    board[1][1] = 'O';
    cout << "\nAfter User Move (O at 1,1):\n";
    printBoard();

    pair<int,int> bestMove = findBestMove();
    cout << "\nAI chooses position: (" 
         << bestMove.first << "," << bestMove.second << ")\n";

    board[bestMove.first][bestMove.second] = 'X';
    cout << "\nBoard after AI Move:\n";
    printBoard();

    return 0;
}
