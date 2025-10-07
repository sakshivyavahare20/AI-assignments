#include <bits/stdc++.h>
using namespace std;


void printBoard(const vector<int> &state) {
    int n = state.size();
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (state[row] == col) cout << "Q ";
            else cout << ". ";
        }
        cout << "\n";
    }
    cout << "-------------------\n";
}


bool isSafe(const vector<int> &state, int row, int col) {
    for (int r = 0; r < row; r++) {
        int c = state[r];
        if (c == col || abs(c - col) == abs(r - row))
            return false;
    }
    return true;
}


void solveDFS(vector<int> &state, int row, int n) {
    if (row == n) {
        printBoard(state);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(state, row, col)) {
            state[row] = col;
            solveDFS(state, row + 1, n);
        }
    }
}


void solveBFS(int n) {
    queue<vector<int>> q;
    q.push(vector<int>()); 

    while (!q.empty()) {
        vector<int> state = q.front();
        q.pop();
        int row = state.size();

        if (row == n) {
            printBoard(state);
            continue;
        }
        for (int col = 0; col < n; col++) {
            if (isSafe(state, row, col)) {
                vector<int> next = state;
                next.push_back(col);
                q.push(next);
            }
        }
    }
}

int main() {
    int n = 8;
    cout << "8-Queens using DFS (Backtracking):\n";
    vector<int> state(n, -1);
    solveDFS(state, 0, n);

    cout << "\n8-Queens using BFS (State-space search):\n";
    solveBFS(n);

    return 0;
}
