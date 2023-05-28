#include "onp.hpp"
#include <bits/stdc++.h>
#include <memory>
using namespace std;

namespace kalkulator {
const array<pair<string, Command>, 5> COMMAND_MAP {
    make_pair("clear", Command::clear),
    make_pair("exit",  Command::exit),
    make_pair("help",  Command::help),
    make_pair("print", Command::print),
    make_pair("set",   Command::set)
};
// const vector<pair<string, Command>> commandMap = {
//     { "clear", Command::clear },
//     { "exit",  Command::exit },
//     { "print", Command::print },
//     { "set",   Command::set }
// };

const array<pair<string, function<unique_ptr<Symbol>()>>, 23> SYMBOL_MAP {
    // 1-argument operators
    make_pair("abs", Abs::create),
    make_pair("sgn", Sgn::create),
    make_pair("floor", Floor::create),
    make_pair("ceil", Ceil::create),
    make_pair("frac", Frac::create),
    make_pair("sin", Sin::create),
    make_pair("cos", Cos::create),
    make_pair("atan", Atan::create),
    make_pair("acot", Acot::create),
    make_pair("ln", Ln::create),
    make_pair("exp", Exp::create),
    // 2-argument operators
    make_pair("+", Add::create),
    make_pair("-", Subtract::create),
    make_pair("*", Multiply::create),
    make_pair("/", Divide::create),
    make_pair("%", Modulo::create),
    make_pair("min", Min::create),
    make_pair("max", Max::create),
    make_pair("log", Log::create),
    make_pair("pow", Pow::create),
    // Stale
    make_pair("e", EConstant::create),
    make_pair("phi", PhiConstant::create),
    make_pair("pi", PiConstant::create)
};

// Liczba ---------------------------------------------------------------------
Liczba::Liczba(double value) : m_value(value) { }
double Liczba::eval(stack<double> &s) { return m_value; }
// Liczba ---------------------------------------------------------------------

// Stala ----------------------------------------------------------------------
double PhiConstant::eval(stack<double> &s) { return 1.618'033'988'749'894'848; }
unique_ptr<PhiConstant> PhiConstant::create() {
    return unique_ptr<PhiConstant>{new PhiConstant};
}

double EConstant::eval(stack<double> &s) { return 2.718'281'828'459'045'235; }
unique_ptr<EConstant> EConstant::create() {
    return unique_ptr<EConstant>{new EConstant};
}

double PiConstant::eval(stack<double> &s) { return 3.141'592'653'589'793'238; }
unique_ptr<PiConstant> PiConstant::create() {
    return unique_ptr<PiConstant>{new PiConstant};
}
// Stala ----------------------------------------------------------------------

// Zmienna --------------------------------------------------------------------
unsigned int Zmienna::MAX_VARIABLE_NAME_LENGTH = 7;
std::map<std::string, double> Zmienna::bindings;

void Zmienna::check_name (string name) {
    for (auto &binding : COMMAND_MAP)
        if (name == binding.first)
            throw invalid_argument("Nazwa zmiennej nie moze byc poleceniem.");
    for (auto &binding : SYMBOL_MAP)
        if (name == binding.first)
            throw invalid_argument("Nazwa zmiennej nie moze byc operatorem.");
    if ('0' <= name[0] and name[0] <= '9')
        throw invalid_argument("Nazwa zmiennej nie moze zaczynac sie od cyfry.");

    if (name.size() > MAX_VARIABLE_NAME_LENGTH)
        throw invalid_argument("Nazwa zmiennej nie moze miec wiecej niz " 
                                + to_string(MAX_VARIABLE_NAME_LENGTH)
                                + " znakow.");
}

Zmienna::Zmienna(string name) {
    check_name(name);

    m_name = name;
}

void Zmienna::set_variable(string name, double value) {
    check_name(name);

    bindings[name] = value;
}

double Zmienna::get_variable(string name) {
    if (bindings.find(name) == bindings.end())
        throw invalid_argument("Zmienna " + name 
                               + " nie ma przypisanej wartosci.");
    return bindings[name];
}


void Zmienna::clear() {
    bindings.clear();
}

string Zmienna::get_name() { return m_name; }
double Zmienna::eval(stack<double> &s) { return get_variable(m_name); }
// Zmienna --------------------------------------------------------------------


// Funkcja --------------------------------------------------------------------
vector<double> Funkcja::pop_stack(stack<double> &s, string function_name) {
    if (s.size() < get_arity())
        throw invalid_argument(function_name + " wymaga " 
                               + to_string(get_arity()) + " argumentow");
    vector<double> result;
    for (unsigned int i = 0; i < get_arity(); i++) {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}
// Funkcja --------------------------------------------------------------------

// Operator1 ------------------------------------------------------------------
unsigned int Operator1::get_arity() { return 1; }
// Operator1 ------------------------------------------------------------------

// Operator1 Derived ----------------------------------------------------------
// abs, sgn, floor, ceil, frac, sin, cos, atan, acot, ln i exp
double Abs::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "abs");
    return abs(args[0]);
}
unique_ptr<Abs> Abs::create() { return unique_ptr<Abs>{new Abs}; };

double Sgn::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "sgn");
    if (args[0] == 0.0)
        return 0.0;
    if (args[0] > 0.0)
        return 1.0;
    return -1.0;
}
unique_ptr<Sgn> Sgn::create() { return unique_ptr<Sgn>{new Sgn}; };

double Floor::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "floor");
    return floor(args[0]);
}
unique_ptr<Floor> Floor::create() { return unique_ptr<Floor>{new Floor}; };

double Ceil::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "ceil");
    return ceil(args[0]);
}
unique_ptr<Ceil> Ceil::create() { return unique_ptr<Ceil>{new Ceil}; };

double Frac::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "frac");
    double intpart;
    return modf(args[0], &intpart);
}
unique_ptr<Frac> Frac::create() { return unique_ptr<Frac>{new Frac}; };

double Sin::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "sin");
    return sin(args[0]);
}
unique_ptr<Sin> Sin::create() { return unique_ptr<Sin>{new Sin}; };

double Cos::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "cos");
    return cos(args[0]);
}
unique_ptr<Cos> Cos::create() { return unique_ptr<Cos>{new Cos}; };

double Atan::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "atan");
    return atan(args[0]);
}
unique_ptr<Atan> Atan::create() { return unique_ptr<Atan>{new Atan}; };

double Acot::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "acot");
    if (args[0] == 0.0)
        throw invalid_argument("acot jest niezdefiniowany dla 0");
    return atan(1.0 / args[0]);
}
unique_ptr<Acot> Acot::create() { return unique_ptr<Acot>{new Acot}; };

double Ln::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "ln");
    return log(args[0]);
}
unique_ptr<Ln> Ln::create() { return unique_ptr<Ln>{new Ln}; };

double Exp::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "exp");
    return exp(args[0]);
}
unique_ptr<Exp> Exp::create() { return unique_ptr<Exp>{new Exp}; };
// Operator1 Derived ----------------------------------------------------------

// Operator2 ------------------------------------------------------------------
unsigned int Operator2::get_arity() { return 2; }
// Operator2 ------------------------------------------------------------------

// Operator2 Derived ----------------------------------------------------------
double Add::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Dodawanie");
    return args[1] + args[0];
}
unique_ptr<Add> Add::create() { return unique_ptr<Add>{new Add}; }

double Subtract::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Odejmowanie");
    return args[1] - args[0];
}
unique_ptr<Subtract> Subtract::create() { return unique_ptr<Subtract>{new Subtract}; }

double Multiply::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Mnozenie");
    return args[1] * args[0];
}
unique_ptr<Multiply> Multiply::create() { return unique_ptr<Multiply>{new Multiply}; }

double Divide::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Dzielenie");
    return args[1] / args[0];
}
unique_ptr<Divide> Divide::create() { return unique_ptr<Divide>{new Divide}; }

double Modulo::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Modulo");
    // https://stackoverflow.com/questions/1521607/check-double-variable-if-it-contains-an-integer-and-not-floating-point
    double intpart;
    double a_frac = modf(args[0], &intpart);
    double b_frac = modf(args[1], &intpart);
    if (a_frac != 0.0 or b_frac != 0.0)
        throw invalid_argument("Modulo wymaga argumentow calkowitych.");
    int a = args[0];
    int b = args[1];
    return b % a;
}
unique_ptr<Modulo> Modulo::create() { return unique_ptr<Modulo>{new Modulo}; }

double Min::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Min");
    return min(args[1], args[0]);
}
unique_ptr<Min> Min::create() { return unique_ptr<Min>{new Min}; }

double Max::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Max");
    return max(args[1], args[0]);
}
unique_ptr<Max> Max::create() { return unique_ptr<Max>{new Max}; }

double Log::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Log");
    return log(args[0]) / log(args[1]);
}
unique_ptr<Log> Log::create() { return unique_ptr<Log>{new Log}; }

double Pow::eval(stack<double> &s) {
    vector<double> args = pop_stack(s, "Pow");
    return pow(args[1], args[0]);
}
unique_ptr<Pow> Pow::create() { return unique_ptr<Pow>{new Pow}; }
// Operator2 Derived ----------------------------------------------------------

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
    if ('0' <= s[0] and s[0] <= '9') {
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
