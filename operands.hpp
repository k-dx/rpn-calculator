#ifndef OPERANDS_HPP
#define OPERANDS_HPP

#include "onp.hpp"
#include <bits/stdc++.h>

namespace kalkulator {
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
}

#endif