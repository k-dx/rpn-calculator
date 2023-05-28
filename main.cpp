#include <bits/stdc++.h>
using namespace std;

#include "onp.hpp"
using namespace kalkulator;

void print_help() {
    cout << "A B - (~ A - B)" << endl;
    cout << "BASE ARGUMENT log" << endl;
    cout << "BASE EXPONENT pow" << endl;
}

int main () {
    // {
    //     cout << "<<< 1 >>>" << endl;
    //     Parser parser;
    //     string s = "set x to 3 1 +";
    //     parser.parse_set(s);
    // }
    // {
    //     cout << "<<< 2 >>>" << endl;
    //     Parser parser;
    //     string s = "set x to 9";
    //     parser.parse_set(s);
    // }
    // {
    //     cout << "<<< 3 >>>" << endl;
    //     Parser parser;
    //     string s = "set x to ";
    //     parser.parse_set(s);
    // }
    // {
    //     cout << "<<< 4 >>>" << endl;
    //     Parser parser;
    //     string s = "set x  to ";
    //     parser.parse_set(s);
    // }
    // {
    //     cout << "<<< 5 >>>" << endl;
    //     Parser parser;
    //     string s = "set     x to ";
    //     parser.parse_set(s);
    // }
    // {
    //     cout << "<<< 6 >>>" << endl;
    //     Parser parser;
    //     string s = "set     x banan ";
    //     parser.parse_set(s);
    // }

    cout << "### Kalkulator ONP ###" << endl;
    cout << "Dostepne polecenia:" << endl;
    cout << " * przypisanie zmiennej: " << endl;
    cout << "    set NAZWA to WYRAZENIE" << endl;
    cout << "    np. set x to 3 1 +" << endl;
    cout << " * obliczenie wartosci wyrazenia: " << endl;
    cout << "    print WYRAZENIE" << endl;
    cout << "    np. print x 1 -" << endl;
    cout << " * wyczyszczenie wartosci zmiennych: " << endl;
    cout << "    clear" << endl;
    cout << " * wyjscie: " << endl;
    cout << "    exit" << endl;

    string s;
    Parser parser;
    const string PROMPT = "> ";
    cout << PROMPT;
    while (getline(cin, s)) {
        Command cmd = parser.parse_command(s);

        if (cmd == Command::clear) {
            Zmienna::clear();
        }
        else if (cmd == Command::exit) {
            break;
        }
        else if (cmd == Command::print) {
            try {
                queue<unique_ptr<Symbol>> parsed = parser.parse_print(s);
                cout << eval(std::move(parsed)) << endl;
            } catch (exception &e) {
                clog << "Blad: " << e.what() << endl;
            }
        }
        else if (cmd == Command::set) {
            try {
                pair<string, queue<unique_ptr<Symbol>>> parsed = parser.parse_set(s);
                double value = eval(std::move(parsed.second));
                Zmienna::set_variable(parsed.first, value);
                cout << value << endl;
            } catch (exception &e) {
                clog << "Blad: " << e.what() << endl;
            }
        }
        else {
            clog << "Blad: Nieznane polecenie." << endl;
        }
        cout << PROMPT;
    }

    return 0;
}

