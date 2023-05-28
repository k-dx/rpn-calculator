#include "operands.hpp"
using namespace std;

namespace kalkulator {
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
    if (name[0] == '-')
        throw invalid_argument("Nazwa zmiennej nie moze zaczynac sie od minusa (-).");
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
}