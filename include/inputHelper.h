#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <iostream>
#include <limits>
#include <string>
using namespace std;

class InputHelper
{
public:
    static int getInt(const string &input);
    static double getDouble(const string &input);
    static string getString(const string &input);
};

#endif