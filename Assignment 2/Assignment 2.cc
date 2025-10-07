#include <bits/stdc++.h>
using namespace std;

vector<string> variables = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};
vector<string> colors = {"Red", "Green", "Blue"};

map<string, vector<string>> neighbors = {
    {"WA", {"NT", "SA"}},
    {"NT", {"WA", "SA", "Q"}},
    {"SA", {"WA", "NT", "Q", "NSW", "V"}},
    {"Q",  {"NT", "SA", "NSW"}},
    {"NSW",{"Q", "SA", "V"}},
    {"V",  {"SA", "NSW"}},
    {"T",  {}} 
};


bool forwardCheck(map<string, vector<string>> &domains, string var, string value) {
    for (string nb : neighbors[var]) {
        if (domains[nb].size() > 1) {
            vector<string> newDomain;
            for (string col : domains[nb]) {
                if (col != value) newDomain.push_back(col);
            }
            domains[nb] = newDomain;

            if (domains[nb].empty()) return false;
        }
    }
    return true;
}

bool backtrack(int index, map<string, string> &assignment, map<string, vector<string>> domains) {
    if (index == variables.size()) return true;

    string var = variables[index];

    for (string value : domains[var]) {
        bool consistent = true;
        for (string nb : neighbors[var]) {
            if (assignment.count(nb) && assignment[nb] == value) {
                consistent = false;
                break;
            }
        }
        if (!consistent) continue;

        // Assign value
        assignment[var] = value;

        map<string, vector<string>> tempDomains = domains;

        if (forwardCheck(domains, var, value)) {
            if (backtrack(index + 1, assignment, domains)) return true;
        }

        domains = tempDomains;
        assignment.erase(var);
    }

    return false;
}

int main() {
    map<string, vector<string>> domains;
    for (string var : variables) {
        domains[var] = colors; 
    }

    map<string, string> assignment;
    if (backtrack(0, assignment, domains)) {
        cout << "Final Assignment:\n";
        for (string var : variables) {
            cout << var << " = " << assignment[var] << "\n";
        }
    } else {
        cout << "No valid coloring found.\n";
    }
}
