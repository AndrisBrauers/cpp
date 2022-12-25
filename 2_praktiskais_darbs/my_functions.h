#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>

using namespace std;

void addNum(vector<int> &vect) {
    string text = "";
    string num = "";
    cin.ignore();
    getline(cin, text);
    
    for (int i = 0; i < text.length(); i++) {
        if (int(text[i]) > 47 && int(text[i]) < 58) {
            num += text[i];
        } else if (num != "") {
            vect.push_back(stoi(num));
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
    map<int, int> m_numbers;
    for (int i = 0; i != vect.size(); i++) {
        m_numbers.insert(pair<int, int>(i, vect[i]));
    }
    for (auto const &tupl: m_numbers) {
        cout << tupl.first << " : " << tupl.second << endl;
    }
}

void printVector(const vector<int> &vect) {
    for (auto i = vect.begin(); i != vect.end(); ++i) {
        cout << *i << " ";
    }
}