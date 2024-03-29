#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void makeMap(const vector<int> &vect, map<int, string> &numMap) {
    string numName;
    vector<int> toErase;

    for (int i = 0; i != vect.size(); i++) {
        if (numMap.count(vect[i]) == 0) {
            cout << "Ievadi skaitli " << vect[i] << " ar vārdiem\n";
            cin >> numName;
            numMap.insert(pair<int, string>(vect[i], numName));
        }
    }
    for (auto const &tupl: numMap) {
        if (find(vect.begin(), vect.end(), tupl.first) == vect.end()) {
            toErase.emplace_back(tupl.first);
        }
    }
    for (int i = 0; i != toErase.size(); i++) {
        numMap.erase(toErase[i]);
    }
}

void addNum(vector<int> &vect) {
    string text = "";
    string num = "";
    vect.clear();
    cin.ignore();
    getline(cin, text);
    
    for (int i = 0; i < text.length(); i++) {
        if (int(text[i]) > 47 && int(text[i]) < 58) {
            num += text[i];
        } else if (num != "") {
            vect.emplace_back(stoi(num));
            num = "";
        }
    }
    if (num != "") {
        vect.emplace_back(stoi(num));
    }
}

void queuePrint(const vector<int> &vect) {
    queue<int> q_numbers;
    for (auto i = vect.begin(); i != vect.end(); ++i) {
        q_numbers.push(*i);
    }

    while (!q_numbers.empty()) {
        cout << q_numbers.front() << ' ';
        q_numbers.pop();
    }
}

void stackPrint(const vector<int> &vect) {
    stack<int> s_numbers;
    for (auto i = vect.begin(); i != vect.end(); ++i) {
        s_numbers.push(*i);
    }

    while (!s_numbers.empty()) {
        cout << s_numbers.top() << ' ';
        s_numbers.pop();
    }
}

void twoStackPrint(const vector<int> &vect) {
    stack<int> s1_numbers;
    stack<int> s2_numbers;
    for (auto i = vect.begin(); i != vect.end(); ++i) {
        s1_numbers.push(*i);
    }

    while (!s1_numbers.empty()) {
        s2_numbers.push(s1_numbers.top());
        s1_numbers.pop();
    }

    while (!s2_numbers.empty()) {
        cout << s2_numbers.top() << ' ';
        s2_numbers.pop();
    }
}

void mapPrint(const vector<int> &vect) {
    map<int, int> numMap;
    for (int i = 0; i != vect.size(); i++) {
        numMap.insert(pair<int, int>(i, vect[i]));
    }
    for (auto const &tupl: numMap) {
        cout << tupl.first << " : " << tupl.second << endl;
    }
}

void setPrint(const vector<int> &vect) {
    set<int> s_numbers;
    for (auto i = vect.begin(); i != vect.end(); ++i) {
        s_numbers.insert(*i);
    }
    for (auto i = s_numbers.begin(); i != s_numbers.end(); i++) {
        cout << *i << " ";
    }
}

void mapExtraPrint(map<int, string> &numMap) {  
    int numKey;
    cout << "Ievadi skaitli kuru atrast: ";
    cin >> numKey;
    cin.clear();
    
    if (numMap.count(numKey) != 0) {
        cout << numMap[numKey] << endl;
    } else {
        cout << "Skaitlis nav atrasts\n";
    }
}

void multimapFind(const vector<int> &vect) {
    multimap <string, int> grades;
    string name;

    for (auto i = vect.begin(); i != vect.end(); ++i) {
        cout << "Ievadi kuram ir atzīme " << *i << endl;
        cin >> name;
        grades.insert(pair<string, int>(name, *i));
    }

    cout << "Kura studenta atzīmes atrast: ";
    cin >> name;

    for (auto const &tupl: grades) {
        if (tupl.first == name) {
            cout << tupl.second << " ";
        }
    }
}

void printVector(const vector<int> &vect) {
    for (auto i = vect.begin(); i != vect.end(); ++i) {
        cout << *i << " ";
    }
}