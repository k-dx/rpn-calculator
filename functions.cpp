// Jakub Dubiel
// Kurs C++
// Lista 11: Kalkulator ONP
// kompilacja: g++ -std=c++17 *.cpp
#include "functions.hpp"
using namespace std;

namespace kalkulator {
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
}