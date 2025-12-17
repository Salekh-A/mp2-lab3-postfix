#include "postfix.h"
#include <iostream>

using namespace std;

int main() {
    try {

        string expressions[] = {
            "2 + 3",
            "2 + 3 * 4",
            "(2 + 3) * 4",
            "10.5 / 2 + 3.5",
            "- 3 - 2 * (- 1) / (-1) + 2 * 1"
        };

        for (int i = 0; i < 5; i++) {
            cout << "\nExpression " << (i + 1) << ": " << expressions[i] << endl;
            TPostfix expr(expressions[i]);
            cout << "  Infix: " << expr.getInfix() << endl;
            cout << "  Postfix: " << expr.getPostfix() << endl;
            cout << "  Result: " << expr.calculate() << endl;
        }

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    cin.ignore();
    cin.get();

    return 0;
}