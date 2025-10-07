#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
using namespace std;

struct Rule {
    vector<string> conditions;  
    string conclusion;          
};

bool canApply(const Rule &rule, const set<string> &facts) {
    for (const string &cond : rule.conditions) {
        if (facts.find(cond) == facts.end())
            return false;
    }
    return true;
}

int main() {
    set<string> facts = {"A", "B"};  

    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"},
        {{"D"}, "E"}
    };

    string goal = "E";
    bool newFactAdded = true;
    bool goalReached = false;

    cout << "Initial facts: ";
    for (auto &f : facts) cout << f << " ";
    cout << "\n\nApplying Forward Chaining...\n";

    while (newFactAdded && !goalReached) {
        newFactAdded = false;

        for (const auto &rule : rules) {
            if (canApply(rule, facts) && facts.find(rule.conclusion) == facts.end()) {
                cout << "Rule fired: ";
                for (auto &c : rule.conditions) cout << c << " ";
                cout << "=> " << rule.conclusion << "\n";

                facts.insert(rule.conclusion);
                newFactAdded = true;

                if (rule.conclusion == goal) {
                    goalReached = true;
                    break;
                }
            }
        }
    }

    cout << "\nFinal facts: ";
    for (auto &f : facts) cout << f << " ";
    cout << "\n";

    if (goalReached)
        cout << "Goal \"" << goal << "\" is reached!\n";
    else
        cout << "Goal not reached.\n";

    return 0;
}
