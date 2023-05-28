#ifndef ONP_HPP
#define ONP_HPP

#include <bits/stdc++.h>
#include "functions.hpp"
#include "operands.hpp"

namespace kalkulator {
enum Command {
    clear, exit, help, set, print, unknown
};

class Symbol {
  public:
    virtual double eval(std::stack<double> &s) = 0;
};

class Parser {
  private:
    std::vector<std::string> split(const std::string &s, char delimiter);
    std::unique_ptr<Symbol> parse_symbol(std::string &s);
  public:
    Command parse_command(std::string s);
    std::pair<std::string, std::queue<std::unique_ptr<Symbol>>> parse_set(
        std::string s
    );
    std::queue<std::unique_ptr<Symbol>> parse_ONPExpression(
        std::vector<std::string>::iterator start,
        std::vector<std::string>::iterator end
    );
    std::queue<std::unique_ptr<Symbol>> parse_print(std::string s);
};

double eval(std::queue<std::unique_ptr<Symbol>> q);
void print_help();


const std::array<std::pair<std::string, Command>, 5> COMMAND_MAP {
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

const std::array<
  std::pair<
    std::string,
    std::function<std::unique_ptr<Symbol>()>
  >,
  23
> SYMBOL_MAP {
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
}

#endif 