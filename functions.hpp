// Jakub Dubiel
// RPN Calculator
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "onp.hpp"
#include <bits/stdc++.h>

namespace calculator {
class Function : public Symbol {
  protected:
    virtual unsigned int get_arity() = 0;
    std::vector<double> pop_stack(
        std::stack<double> &s,
        std::string function_name
    );
};

class Operator1 : public Function {
  protected:
    unsigned int get_arity();
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

class Operator2 : public Function {
  protected:
    unsigned int get_arity();
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
}

#endif