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
    std::make_pair("clear", Command::clear),
    std::make_pair("exit",  Command::exit),
    std::make_pair("help",  Command::help),
    std::make_pair("print", Command::print),
    std::make_pair("set",   Command::set)
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
    std::make_pair("abs", Abs::create),
    std::make_pair("sgn", Sgn::create),
    std::make_pair("floor", Floor::create),
    std::make_pair("ceil", Ceil::create),
    std::make_pair("frac", Frac::create),
    std::make_pair("sin", Sin::create),
    std::make_pair("cos", Cos::create),
    std::make_pair("atan", Atan::create),
    std::make_pair("acot", Acot::create),
    std::make_pair("ln", Ln::create),
    std::make_pair("exp", Exp::create),
    // 2-argument operators
    std::make_pair("+", Add::create),
    std::make_pair("-", Subtract::create),
    std::make_pair("*", Multiply::create),
    std::make_pair("/", Divide::create),
    std::make_pair("%", Modulo::create),
    std::make_pair("min", Min::create),
    std::make_pair("max", Max::create),
    std::make_pair("log", Log::create),
    std::make_pair("pow", Pow::create),
    // Stale
    std::make_pair("e", EConstant::create),
    std::make_pair("phi", PhiConstant::create),
    std::make_pair("pi", PiConstant::create)
};
}

#endif 