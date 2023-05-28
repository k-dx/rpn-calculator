#ifndef ONP_HPP
#define ONP_HPP

#include <bits/stdc++.h>

// typedef vector<Symbol> ONPExp;

namespace kalkulator {
enum Command {
    clear, exit, set, print, unknown
};

class Symbol {
  public:
    virtual double eval(std::stack<double> &s) = 0;
};

class Operand : public Symbol {
  public:
    virtual double eval(std::stack<double> &s) = 0;
};

class Liczba : public Operand {
    double m_value;
  public:
    Liczba(double value);
    double eval(std::stack<double> &s);
};

class Stala : public Operand {
  public:
    virtual double eval(std::stack<double> &s) = 0;
};

class PhiConstant : public Stala {
  public:
    double eval(std::stack<double> &s);
};
class EConstant : public Stala {
  public:
    double eval(std::stack<double> &s);
};
class PiConstant : public Stala {
  public:
    double eval(std::stack<double> &s);
};

class Zmienna : public Operand {
    static std::map<std::string, double> bindings;
    static unsigned int MAX_VARIABLE_NAME_LENGTH;
    static void check_name(std::string name);
    std::string m_name;
  public:
    Zmienna(std::string name);

    static void set_variable(std::string name, double value);
    static double get_variable(std::string name);
    static void clear();

    std::string get_name();
    double eval(std::stack<double> &s);
};

class Funkcja : public Symbol {
  protected:
    virtual unsigned int get_arity() = 0;
    std::vector<double> pop_stack(
        std::stack<double> &s,
        std::string function_name
    );
  public:
    virtual double eval(std::stack<double> &s) = 0;
};

class Operator1 : public Funkcja {
  protected:
    unsigned int get_arity();
  public:
    virtual double eval(std::stack<double> &s) = 0;
};

// abs, sgn, floor, ceil, frac, sin, cos, atan, acot, ln i exp
class Abs : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Sgn : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Floor : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Ceil : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Frac : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Sin : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Cos : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Atan : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Acot : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Ln : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};
class Exp : public Operator1 {
  public:
    double eval(std::stack<double> &s);
};

class Operator2 : public Funkcja {
  protected:
    unsigned int get_arity();
  public:
    virtual double eval(std::stack<double> &s) = 0;
};

class Add : public Operator2 {
  public:
    double eval(std::stack<double> &s);
};
class Subtract : public Operator2 {
  public:
    double eval(std::stack<double> &s);
};
class Multiply : public Operator2 {
  public:
    double eval(std::stack<double> &s);
};
class Divide : public Operator2 {
  public:
    double eval(std::stack<double> &s);
};
class Modulo : public Operator2 {
  public:
    double eval(std::stack<double> &s);
};
class Min : public Operator2 {
  public:
    double eval(std::stack<double> &s);
};
class Max : public Operator2 {
  public:
    double eval(std::stack<double> &s);
};
class Log : public Operator2 {
  public:
    double eval(std::stack<double> &s);
};
class Pow : public Operator2 {
  public:
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
}

#endif 