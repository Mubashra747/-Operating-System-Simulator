#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    string filename;
    cout << "**************************************\n";
    cout << "          Create File\n";
    cout << "**************************************\n";
    cout << "Enter filename (or 'q' to quit): ";
    cin >> filename;
    if (filename == "q") return 0;
    filename = "data/" + filename;
    FILE* fp = fopen(filename.c_str(), "w");
    if (fp) {
        cout << "File created: " << filename << "\n";
        fclose(fp);
    } else {
        cout << "Error creating file\n";
    }
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
