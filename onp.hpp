#ifndef ONP_HPP
#define ONP_HPP

#include <bits/stdc++.h>

namespace kalkulator {
enum Command {
    clear, exit, help, set, print, unknown
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
    static std::unique_ptr<PhiConstant> create();
};
class EConstant : public Stala {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<EConstant> create();
};
class PiConstant : public Stala {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<PiConstant> create();
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

class Abs : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Abs> create();
};
class Sgn : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Sgn> create();
};
class Floor : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Floor> create();
};
class Ceil : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Ceil> create();
};
class Frac : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Frac> create();
};
class Sin : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Sin> create();
};
class Cos : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Cos> create();
};
class Atan : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Atan> create();
};
class Acot : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Acot> create();
};
class Ln : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Ln> create();
};
class Exp : public Operator1 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Exp> create();
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
    static std::unique_ptr<Add> create();
};
class Subtract : public Operator2 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Subtract> create();
};
class Multiply : public Operator2 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Multiply> create();
};
class Divide : public Operator2 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Divide> create();
};
class Modulo : public Operator2 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Modulo> create();
};
class Min : public Operator2 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Min> create();
};
class Max : public Operator2 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Max> create();
};
class Log : public Operator2 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Log> create();
};
class Pow : public Operator2 {
  public:
    double eval(std::stack<double> &s);
    static std::unique_ptr<Pow> create();
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