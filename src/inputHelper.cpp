#include "inputHelper.h"

int InputHelper::getInt(const string &input)
{
    int value;

    while (true)
    {
        cout << input;
        cin >> value;

        if (!cin.fail())
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid input. Please enter a valid integer.\n";
    }
}

double InputHelper::getDouble(const string &input)
{
    double value;

    while (true)
    {
        cout << input;
        cin >> value;

        if (!cin.fail())
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid input. Please enter a valid number.\n";
    }
}

string InputHelper::getString(const string &input)
{
    string value;
    cout << input;
    getline(cin, value);
    return value;
}