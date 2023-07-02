// Jakub Dubiel
// RPN Calculator
#include <bits/stdc++.h>
using namespace std;

#include "onp.hpp"
using namespace calculator;

#include "lang.hpp"

int main (int argc, char* argv[]) {
    int language = lang::EN;
    if (argc == 2 and strcmp(argv[1], "pl") == 0) {
        language = lang::PL;
    }
    lang::init(language);


    cout << lang::get(lang::welcome_message) << endl;

    string s;
    Parser parser;
    const string PROMPT = "> ";
    cout << PROMPT;
    while (getline(cin, s)) {
        Command cmd = parser.parse_command(s);

        if (cmd == Command::clear) {
            Variable::clear();
        }
        else if (cmd == Command::exit) {
            break;
        }
        else if (cmd == Command::help) {
            print_help();
        }
        else if (cmd == Command::print) {
            try {
                queue<unique_ptr<Symbol>> parsed = parser.parse_print(s);
                cout << eval(std::move(parsed)) << endl;
            } catch (exception &e) {
                clog << lang::get(lang::error) << ": " << e.what() << endl;
            }
        }
        else if (cmd == Command::set) {
            try {
                pair<string, queue<unique_ptr<Symbol>>> parsed = parser.parse_set(s);
                double value = eval(std::move(parsed.second));
                Variable::set_variable(parsed.first, value);
                cout << value << endl;
            } catch (exception &e) {
                clog << lang::get(lang::error) << ": " << e.what() << endl;
            }
        }
        else {
            clog << lang::get(lang::error) << ": " 
            << lang::get(lang::unknown_command) << endl;
        }
        cout << PROMPT;
    }

    return 0;
}

