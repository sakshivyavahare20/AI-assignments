#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

struct Rule {
    vector<string> conditions;   
    string conclusion;           
};

bool backwardChaining(const string &goal,
                      const set<string> &facts,
                      const vector<Rule> &rules,
                      set<string> &visited) {
    if (facts.find(goal) != facts.end()) {
        cout << "Fact found: " << goal << "\n";
        return true;
    }

    if (visited.find(goal) != visited.end())
        return false;
    visited.insert(goal);

    for (const Rule &rule : rules) {
        if (rule.conclusion == goal) {
            cout << "Trying rule to prove " << goal << ": IF ";
            for (size_t i = 0; i < rule.conditions.size(); i++) {
                cout << rule.conditions[i];
                if (i < rule.conditions.size() - 1) cout << " AND ";
            }
            cout << " THEN " << goal << "\n";

            bool allTrue = true;
            for (const string &subGoal : rule.conditions) {
                if (!backwardChaining(subGoal, facts, rules, visited)) {
                    allTrue = false;
                    break;
                }
            }
            if (allTrue) return true;
        }
    }
    return false;
}

int main() {
    set<string> facts = {"A", "B"};

    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"},
        {{"D"}, "E"}
    };

    string goal = "E"; 
    set<string> visited; 

    cout << "Backward Chaining to prove: " << goal << "\n";
    cout << "---------------------------------\n";

    if (backwardChaining(goal, facts, rules, visited))
        cout << "\nGoal \"" << goal << "\" is PROVED!\n";
    else
        cout << "\nGoal \"" << goal << "\" cannot be proved.\n";

    return 0;
}
