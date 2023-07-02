// Jakub Dubiel
// RPN Calculator
#include "lang.hpp"
using namespace std;

array<string, 22> lang::TRANSLATIONS;

void lang::init(int language) {

    if (language == EN) {
        TRANSLATIONS[welcome_message] = 
            "### RPN Calculator ###\n"
            "Available commands:\n"
            " * initialize variable: \n"
            "    set NAME to EXPRESSION\n"
            "    NAME cannot be command or operator name\n"
            "    and cannot start with a digit or minus (-)\n"
            "    e.g. set x to 3 1 +\n"
            " * get value of an expression: \n"
            "    print EXPRESSION\n"
            "    np. print x 1 -\n"
            " * clear values of variables: \n"
            "    clear\n"
            " * exit: \n"
            "    exit\n"
            " * help: \n"
            "    help";
        TRANSLATIONS[error] = "Error";
        TRANSLATIONS[unknown_command] = "Unknown command.";
        TRANSLATIONS[varname_cannot_be_command] 
            = "Variable name cannot be a command.";
        TRANSLATIONS[varname_cannot_be_operator] 
            = "Variable name cannot be an operator.";
        TRANSLATIONS[varname_cannot_start_with_digit] 
            = "Variable name cannot start with a digit.";
        TRANSLATIONS[varname_cannot_start_with_minus] 
            = "Variable name cannot start with a minus (-).";
        TRANSLATIONS[varname_cannot_be_longer_than] 
            = "Variable name cannot be longer than";
        TRANSLATIONS[characters] = "characters.";
        TRANSLATIONS[variable] = "Variable";
        TRANSLATIONS[does_not_have_value] = "does not have a value set.";
        TRANSLATIONS[invalid_set_syntax] = "Bad syntax of set command.";
        TRANSLATIONS[bad_expression] = "Bad expression";
        TRANSLATIONS[available_operators] = "Available operators";
        TRANSLATIONS[needs] = "requires";
        TRANSLATIONS[arguments] = "arguments";
        TRANSLATIONS[is_not_defined_for] = "is undefined for";
        TRANSLATIONS[addition] = "Addition";
        TRANSLATIONS[subtraction] = "Subraction";
        TRANSLATIONS[multiplication] = "Multiplication";
        TRANSLATIONS[division] = "Division";
        TRANSLATIONS[needs_integer_arguments] = "requires integer arguments.";
    }
    else if (language == PL) {
        TRANSLATIONS[welcome_message] = 
            "### Kalkulator ONP ###\n"
            "Dostepne polecenia:\n"
            " * przypisanie zmiennej: \n"
            "    set NAZWA to WYRAZENIE\n"
            "    NAZWA nie moze byc nazwa polecenia ani operatora\n"
            "    i nie moze zaczynac sie od cyfry ani minusa (-)\n"
            "    np. set x to 3 1 +\n"
            " * obliczenie wartosci wyrazenia: \n"
            "    print WYRAZENIE\n"
            "    np. print x 1 -\n"
            " * wyczyszczenie wartosci zmiennych: \n"
            "    clear\n"
            " * wyjscie: \n"
            "    exit\n"
            " * pomoc: \n"
            "    help";
        TRANSLATIONS[error] = "Blad";
        TRANSLATIONS[unknown_command] = "Nieznane polecenie.";
        TRANSLATIONS[varname_cannot_be_command] 
            = "Nazwa zmiennej nie moze byc poleceniem.";
        TRANSLATIONS[varname_cannot_be_operator] 
            = "Nazwa zmiennej nie moze byc operatorem.";
        TRANSLATIONS[varname_cannot_start_with_digit] 
            = "Nazwa zmiennej nie moze zaczynac sie od cyfry.";
        TRANSLATIONS[varname_cannot_start_with_minus] 
            = "Nazwa zmiennej nie moze zaczynac sie od minusa (-).";
        TRANSLATIONS[varname_cannot_be_longer_than] 
            = "Nazwa zmiennej nie moze miec wiecej niz";
        TRANSLATIONS[characters] = "znakow.";
        TRANSLATIONS[variable] = "Zmienna";
        TRANSLATIONS[does_not_have_value] = "nie ma przypisanej wartosci.";
        TRANSLATIONS[invalid_set_syntax] = "Niepoprawna skladnia polecenia set.";
        TRANSLATIONS[bad_expression] = "Wyrazenie jest niepoprawne";
        TRANSLATIONS[available_operators] = "Dostepne operatory";
        TRANSLATIONS[needs] = "wymaga";
        TRANSLATIONS[arguments] = "argumentow";
        TRANSLATIONS[is_not_defined_for] = "jest niezdefiniowany dla";
        TRANSLATIONS[addition] = "Dodawanie";
        TRANSLATIONS[subtraction] = "Odejmowanie";
        TRANSLATIONS[multiplication] = "Mnozenie";
        TRANSLATIONS[division] = "Dzielenie";
        TRANSLATIONS[needs_integer_arguments] = "wymaga argumentow calkowitych.";
    }
    else {
        throw invalid_argument("Bad language given");
    }
}

std::string lang::get(int message_name) {
    return TRANSLATIONS[message_name];
}
