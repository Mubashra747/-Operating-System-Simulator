#include <iostream>
#include <iomanip>
#include <unistd.h>
using namespace std;

int main() {
    string filename;
    cout << "**************************************\n";
    cout << "          Delete File\n";
    cout << "**************************************\n";
    cout << "Enter filename (or 'q' to quit): ";
    cin >> filename;
    if (filename == "q") return 0;
    filename = "data/" + filename;
    if (unlink(filename.c_str()) == 0) {
        cout << "File deleted: " << filename << "\n";
    } else {
        cout << "Error deleting file\n";
    }
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
