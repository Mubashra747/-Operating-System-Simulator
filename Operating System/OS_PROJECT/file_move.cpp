#include <iostream>
#include <iomanip>
#include <unistd.h>
using namespace std;

int main() {
    string src, dest;
    cout << "**************************************\n";
    cout << "           Move File\n";
    cout << "**************************************\n";
    cout << "Enter source filename (or 'q' to quit): ";
    cin >> src;
    if (src == "q") return 0;
    cout << "Enter destination filename: ";
    cin >> dest;
    src = "data/" + src;
    dest = "data/" + dest;
    if (rename(src.c_str(), dest.c_str()) == 0) {
        cout << "File moved: " << src << " to " << dest << "\n";
    } else {
        cout << "Error moving file\n";
    }
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
