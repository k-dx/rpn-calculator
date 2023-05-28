#include "onp.hpp"
#include "functions.hpp"
#include "operands.hpp"
#include <bits/stdc++.h>
#include <memory>
using namespace std;

namespace kalkulator {
// Parser ---------------------------------------------------------------------
Command Parser::parse_command(string s) {
    string command = s.substr(0, s.find(' '));
    for (auto &binding : COMMAND_MAP)
        if (command == binding.first)
            return binding.second;
    return Command::unknown;
}

vector<string> Parser::split(const string &s, char delimiter) {
    vector<string> result;
    string buffer = "";
    for (char c : s) {
        if (c == delimiter) {
            if (buffer != "")
                result.push_back(buffer);
            buffer = "";
        }
        else {
            buffer += c;
        }
    }
    if (buffer != "")
        result.push_back(buffer);
    return result;
}

pair<string, queue<unique_ptr<Symbol>>> Parser::parse_set(string s) {
    vector<string> parts = split(s, ' ');
    if (parts[0] != "set" or parts[2] != "to")
        throw invalid_argument("Niepoprawna skladnia polecenia set.");
    
    // cerr << "command = |" << parts[0] << "|" << endl;
    // cerr << "var_name = |" << parts[1] << "|" << endl;
    // cerr << "to = |" << parts[2] << "|" << endl;

    return { parts[1], parse_ONPExpression(parts.begin()+3, parts.end()) };
}

unique_ptr<Symbol> Parser::parse_symbol (string &s) {
    for (auto &binding : SYMBOL_MAP)
        if (s == binding.first)
            return binding.second();

    // Liczba
    if (('0' <= s[0] and s[0] <= '9') or s[0] == '-') {
        return unique_ptr<Symbol>{new Liczba(stod(s))};
    // Zmienna
    } else {
        return unique_ptr<Symbol>{new Zmienna(s)};
    }
}

queue<unique_ptr<Symbol>> Parser::parse_ONPExpression(
    vector<string>::iterator start,
    vector<string>::iterator end
) {
    queue<unique_ptr<Symbol>> result;
    for (auto it = start; it != end; it++) {
        result.push(parse_symbol(*it));
    }

    return result;
}
queue<unique_ptr<Symbol>> Parser::parse_print(string s) {
    vector<string> parts = split(s, ' ');
    return parse_ONPExpression(parts.begin()+1, parts.end());
}
// parse ----------------------------------------------------------------------

// eval -----------------------------------------------------------------------
double eval(queue<unique_ptr<Symbol>> q) {
    stack<double> s;
    while (!q.empty()) {
        // https://stackoverflow.com/questions/14127487/remove-unique-ptr-from-queue
        auto e = std::move(q.front());
        q.pop();
        s.push(e->eval(s));
    }
    if (s.size() != 1)
        throw invalid_argument("Wyrazenie jest niepoprawne");
    return s.top();
}
// eval -----------------------------------------------------------------------

// print_help -----------------------------------------------------------------
void print_help() {
    cout << "Dostepne operatory: ";
    for (auto &e : SYMBOL_MAP)
        cout << e.first << ", ";
    cout << endl;
    cout << "Info:" << endl;
    cout << "A B - (~ A - B)" << endl;
    cout << "BASE ARGUMENT log" << endl;
    cout << "BASE EXPONENT pow" << endl;
}
// print_help -----------------------------------------------------------------
}
