#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

int main() {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    cout << "**************************************\n";
    cout << "            Calendar\n";
    cout << "**************************************\n";
    cout << "Date: " << t->tm_mday << "/" << t->tm_mon + 1 << "/" << t->tm_year + 1900 << "\n";
    cout << "Day: ";
    switch (t->tm_wday) {
        case 0: cout << "Sunday"; break;
        case 1: cout << "Monday"; break;
        case 2: cout << "Tuesday"; break;
        case 3: cout << "Wednesday"; break;
        case 4: cout << "Thursday"; break;
        case 5: cout << "Friday"; break;
        case 6: cout << "Saturday"; break;
    }
    cout << "\nPress 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
