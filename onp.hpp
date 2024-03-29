// Jakub Dubiel
// RPN Calculator
#ifndef ONP_HPP
#define ONP_HPP

#include <bits/stdc++.h>

namespace calculator {
enum Command {
    clear, exit, help, set, print, unknown
};

class Symbol {
  public:
    virtual double eval(std::stack<double> &s) = 0;
};

class Operand : public Symbol { };

class Number : public Operand {
    double m_value;
  public:
    Number(double value);
    double eval(std::stack<double> &s);
};

class Constant : public Operand { };

class PhiConstant : public Constant {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<PhiConstant> create();
};
class EConstant : public Constant {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<EConstant> create();
};
class PiConstant : public Constant {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<PiConstant> create();
};

class Variable : public Operand {
    static std::map<std::string, double> bindings;
    static unsigned int MAX_VARIABLE_NAME_LENGTH;
    static void check_name(std::string name);
    std::string m_name;
  public:
    Variable(std::string name);

    static void set_variable(std::string name, double value);
    static double get_variable(std::string name);
    static void clear();

    std::string get_name();
    double eval(std::stack<double> &s);
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
}

#endif 