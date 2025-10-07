#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const string GOAL = "123456780"; 

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

struct Node {
    string state;
    vector<string> path; 
};

void printState(const string &s) {
    for (int i = 0; i < 9; i++) {
        cout << (s[i] == '0' ? "_ " : string(1, s[i]) + " ");
        if ((i + 1) % 3 == 0) cout << "\n";
    }
    cout << "-------\n";
}

vector<string> getNeighbors(const string &s) {
    vector<string> result;
    int pos = s.find('0');
    int r = pos / 3, c = pos % 3;

    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
            string next = s;
            swap(next[r * 3 + c], next[nr * 3 + nc]);
            result.push_back(next);
        }
    }
    return result;
}

void solveBFS(const string &start) {
    cout << "BFS Search:\n";
    queue<Node> q;
    set<string> visited;

    q.push({start, {start}});
    visited.insert(start);

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.state == GOAL) {
            cout << "Solution found in " << cur.path.size() - 1 << " moves.\n";
            for (auto &st : cur.path) printState(st);
            return;
        }

        for (auto &nbr : getNeighbors(cur.state)) {
            if (!visited.count(nbr)) {
                auto newPath = cur.path;
                newPath.push_back(nbr);
                q.push({nbr, newPath});
                visited.insert(nbr);
            }
        }
    }
    cout << "No solution found (BFS).\n";
}

// ---------------- DFS (limited depth) ----------------
bool dfsUtil(const string &state, int depth, int limit,
             set<string> &visited, vector<string> &path) {
    if (state == GOAL) return true;
    if (depth == limit) return false;

    for (auto &nbr : getNeighbors(state)) {
        if (!visited.count(nbr)) {
            visited.insert(nbr);
            path.push_back(nbr);
            if (dfsUtil(nbr, depth + 1, limit, visited, path)) return true;
            path.pop_back();
            visited.erase(nbr);
        }
    }
    return false;
}

void solveDFS(const string &start, int limit = 15) {
    cout << "DFS Search (depth limit " << limit << "):\n";
    set<string> visited;
    vector<string> path = {start};
    visited.insert(start);

    if (dfsUtil(start, 0, limit, visited, path)) {
        cout << "Solution found in " << path.size() - 1 << " moves.\n";
        for (auto &st : path) printState(st);
    } else {
        cout << "No solution found up to depth " << limit << ".\n";
    }
}

int main() {
    string start = "123405786"; 
    solveBFS(start);

    cout << "\n";
    solveDFS(start, 12); 

    return 0;
}
