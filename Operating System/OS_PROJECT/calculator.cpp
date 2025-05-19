#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    char op;
    double a, b;
    char quit;
    cout << "**************************************\n";
    cout << "           Calculator\n";
    cout << "**************************************\n";
    while (true) {
        cout << "Enter operation (+, -, *, /) or 'q' to quit: ";
        cin >> quit;
        if (quit == 'q') break;
        op = quit;
        cout << "Enter two numbers: ";
        cin >> a >> b;
        switch (op) {
            case '+': cout << "Result: " << a + b << "\n"; break;
            case '-': cout << "Result: " << a - b << "\n"; break;
            case '*': cout << "Result: " << a * b << "\n"; break;
            case '/': 
                if (b != 0) cout << "Result: " << a / b << "\n";
                else cout << "Error: Division by zero\n";
                break;
            default: cout << "Invalid operation\n";
        }
    }
    return 0;
}
