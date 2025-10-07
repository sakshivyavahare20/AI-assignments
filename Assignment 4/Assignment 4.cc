#include <bits/stdc++.h>
using namespace std;

// Edge structure (to -> cost)
struct Edge {
    string to;
    int cost;
};

// Heuristic values (h(n)) = estimated cost to reach goal
unordered_map<string, int> heuristic = {
    {"Pune", 150},
    {"Expressway", 100},
    {"OldHighway", 120},
    {"CoastalRoad", 180},
    {"Mumbai", 0}
};

// Graph definition (adjacency list)
unordered_map<string, vector<Edge>> graph = {
    {"Pune", {{"Expressway", 50}, {"OldHighway", 30}, {"CoastalRoad", 20}}},
    {"Expressway", {{"Mumbai", 100}}},
    {"OldHighway", {{"Mumbai", 120}}},
    {"CoastalRoad", {{"Mumbai", 180}}},
    {"Mumbai", {}}
};

// Node structure for priority queue
struct Node {
    string name;
    int g; // cost so far
    int f; // g + h
    bool operator>(const Node &other) const {
        return f > other.f; // min-heap
    }
};

// A* Algorithm
vector<string> aStar(string start, string goal) {
    priority_queue<Node, vector<Node>, greater<Node>> openList;
    unordered_map<string, int> gScore;
    unordered_map<string, string> parent;
    unordered_set<string> closed;

    gScore[start] = 0;
    openList.push({start, 0, heuristic[start]});

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        if (current.name == goal) {
            // Reconstruct path
            vector<string> path;
            string node = goal;
            while (!node.empty()) {
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());
            cout << "Total cost = " << gScore[goal] << " km\n";
            return path;
        }

        if (closed.count(current.name)) continue;
        closed.insert(current.name);

        for (auto &edge : graph[current.name]) {
            int tentative_g = gScore[current.name] + edge.cost;
            if (!gScore.count(edge.to) || tentative_g < gScore[edge.to]) {
                gScore[edge.to] = tentative_g;
                parent[edge.to] = current.name;
                int f = tentative_g + heuristic[edge.to];
                openList.push({edge.to, tentative_g, f});
            }
        }
    }

    return {}; // No path found
}

// Driver Code
int main() {
    string start = "Pune";
    string goal = "Mumbai";

    vector<string> path = aStar(start, goal);

    if (!path.empty()) {
        cout << "Optimal Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
