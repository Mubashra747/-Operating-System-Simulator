#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(NULL));
    int number = rand() % 100 + 1;
    int guess;
    cout << "**************************************\n";
    cout << "        Number Guessing Game\n";
    cout << "**************************************\n";
    cout << "Guess a number between 1 and 100 (or 'q' to quit):\n";
    while (true) {
        cin >> guess;
        if (cin.fail()) {
            cin.clear();
            string input;
            cin >> input;
            if (input == "q") break;
            cout << "Invalid input. Try again: ";
            continue;
        }
        if (guess < number) cout << "Too low! Try again: ";
        else if (guess > number) cout << "Too high! Try again: ";
        else {
            cout << "Correct! You win!\n";
            break;
        }
    }
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
