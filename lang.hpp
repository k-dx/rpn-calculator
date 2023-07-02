// Jakub Dubiel
// RPN Calculator
#ifndef LANG_HPP
#define LANG_HPP

#include <bits/stdc++.h>

class lang {
  private:
    static std::array<std::string, 22> TRANSLATIONS;
  public:
    static void init(int language);
    static std::string get(int message_name);

    static const int EN = 0;
    static const int PL = 1;

    static const int welcome_message = 0;
    static const int error = 1;
    static const int unknown_command = 2;
    static const int varname_cannot_be_command = 3;
    static const int varname_cannot_be_operator = 4;
    static const int varname_cannot_start_with_digit = 5;
    static const int varname_cannot_start_with_minus = 6;
    static const int varname_cannot_be_longer_than = 7;
    static const int characters = 8;
    static const int variable = 9;
    static const int does_not_have_value = 10;
    static const int invalid_set_syntax = 11;
    static const int bad_expression = 12;
    static const int available_operators = 13;
    static const int needs = 14;
    static const int arguments = 15;
    static const int is_not_defined_for = 16;
    static const int addition = 17;
    static const int subtraction = 18;
    static const int multiplication = 19;
    static const int division = 20;
    static const int needs_integer_arguments = 21;
};

#endif