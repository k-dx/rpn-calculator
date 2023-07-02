// Jakub Dubiel
// RPN Calculator
#include "onp.hpp"
#include "functions.hpp"
#include "lang.hpp"
#include <bits/stdc++.h>
#include <memory>
using namespace std;

namespace calculator {
const array<pair<string, Command>, 5> COMMAND_MAP {
    make_pair("clear", Command::clear),
    make_pair("exit",  Command::exit),
    make_pair("help",  Command::help),
    make_pair("print", Command::print),
    make_pair("set",   Command::set)
};

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
    // Constants
    make_pair("e", EConstant::create),
    make_pair("phi", PhiConstant::create),
    make_pair("pi", PiConstant::create)
};

// Number ---------------------------------------------------------------------
Number::Number(double value) : m_value(value) { }
double Number::eval(stack<double> &s) { return m_value; }
// Number ---------------------------------------------------------------------

// Constant ------------------------------------------------------------------
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
// Constant ------------------------------------------------------------------

// Variable ------------------------------------------------------------------
unsigned int Variable::MAX_VARIABLE_NAME_LENGTH = 7;
std::map<std::string, double> Variable::bindings;

void Variable::check_name (string name) {
    for (auto &binding : COMMAND_MAP)
        if (name == binding.first)
            throw invalid_argument(lang::get(lang::varname_cannot_be_command));
    for (auto &binding : SYMBOL_MAP)
        if (name == binding.first)
            throw invalid_argument(lang::get(lang::varname_cannot_be_operator));
    if ('0' <= name[0] and name[0] <= '9')
        throw invalid_argument(lang::get(lang::varname_cannot_start_with_digit));
    if (name[0] == '-')
        throw invalid_argument(lang::get(lang::varname_cannot_start_with_minus));
    if (name.size() > MAX_VARIABLE_NAME_LENGTH)
        throw invalid_argument(lang::get(lang::varname_cannot_be_longer_than) 
                                + " "
                                + to_string(MAX_VARIABLE_NAME_LENGTH)
                                + " "
                                + lang::get(lang::characters));
}

Variable::Variable(string name) {
    check_name(name);

    m_name = name;
}

void Variable::set_variable(string name, double value) {
    check_name(name);

    bindings[name] = value;
}

double Variable::get_variable(string name) {
    if (bindings.find(name) == bindings.end())
        throw invalid_argument(lang::get(lang::variable) + " " + name + " "
                               + lang::get(lang::does_not_have_value));
    return bindings[name];
}


void Variable::clear() {
    bindings.clear();
}

string Variable::get_name() { return m_name; }
double Variable::eval(stack<double> &s) { return get_variable(m_name); }
// Variable -------------------------------------------------------------------

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
        throw invalid_argument(lang::get(lang::invalid_set_syntax));
    
    // cerr << "command = |" << parts[0] << "|" << endl;
    // cerr << "var_name = |" << parts[1] << "|" << endl;
    // cerr << "to = |" << parts[2] << "|" << endl;

    return { parts[1], parse_ONPExpression(parts.begin()+3, parts.end()) };
}

unique_ptr<Symbol> Parser::parse_symbol (string &s) {
    for (auto &binding : SYMBOL_MAP)
        if (s == binding.first)
            return binding.second();

    // Number
    if (('0' <= s[0] and s[0] <= '9') or s[0] == '-') {
        return unique_ptr<Symbol>{new Number(stod(s))};
    // Variable
    } else {
        return unique_ptr<Symbol>{new Variable(s)};
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
        throw invalid_argument(lang::get(lang::bad_expression));
    return s.top();
}
// eval -----------------------------------------------------------------------

// print_help -----------------------------------------------------------------
void print_help() {
    cout << lang::get(lang::available_operators) + ": ";
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
