#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    string src, dest;
    cout << "**************************************\n";
    cout << "           Copy File\n";
    cout << "**************************************\n";
    cout << "Enter source filename (or 'q' to quit): ";
    cin >> src;
    if (src == "q") return 0;
    cout << "Enter destination filename: ";
    cin >> dest;
    src = "data/" + src;
    dest = "data/" + dest;
    FILE* in = fopen(src.c_str(), "r");
    FILE* out = fopen(dest.c_str(), "w");
    if (in && out) {
        char c;
        while (fread(&c, 1, 1, in)) {
            fwrite(&c, 1, 1, out);
        }
        cout << "File copied: " << src << " to " << dest << "\n";
        fclose(in);
        fclose(out);
    } else {
        cout << "Error copying file\n";
    }
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
