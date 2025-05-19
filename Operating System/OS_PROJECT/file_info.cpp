#include <iostream>
#include <iomanip>
#include <sys/stat.h>
#include <time.h>
using namespace std;

int main() {
    string filename;
    cout << "**************************************\n";
    cout << "           File Info\n";
    cout << "**************************************\n";
    cout << "Enter filename (or 'q' to quit): ";
    cin >> filename;
    if (filename == "q") return 0;
    filename = "data/" + filename;
    struct stat s;
    if (stat(filename.c_str(), &s) == 0) {
        cout << "Size: " << s.st_size << " bytes\n";
        cout << "Created: " << ctime(&s.st_ctime);
        cout << "Modified: " << ctime(&s.st_mtime);
    } else {
        cout << "Error getting file info\n";
    }
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
