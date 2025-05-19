#include <iostream>
#include <iomanip>
#include <unistd.h>
using namespace std;

int main() {
    string filename;
    cout << "**************************************\n";
    cout << "           Print File\n";
    cout << "**************************************\n";
    cout << "Enter filename (or 'q' to quit): ";
    cin >> filename;
    if (filename == "q") return 0;
    filename = "data/" + filename;
    FILE* fp = fopen(filename.c_str(), "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            cout << line;
            sleep(1);
        }
        fclose(fp);
    } else {
        cout << "Error reading file\n";
    }
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
