#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(NULL));
    int type;
    cout << "**************************************\n";
    cout << "           Dice Roller\n";
    cout << "**************************************\n";
    cout << "Enter die type (6 for D6, 20 for D20, or 0 to quit): ";
    cin >> type;
    if (type == 0) return 0;
    if (type == 6 || type == 20) {
        int roll = rand() % type + 1;
        cout << "You rolled a " << roll << "\n";
    } else {
        cout << "Invalid die type\n";
    }
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
