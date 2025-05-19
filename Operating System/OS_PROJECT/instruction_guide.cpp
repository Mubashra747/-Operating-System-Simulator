#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "**************************************\n";
    cout << "        Instruction Guide\n";
    cout << "**************************************\n";
    cout << left << setw(20) << "Task" << "Description\n";
    cout << string(50, '-') << "\n";
    cout << setw(20) << "Calculator" << "Performs basic arithmetic operations.\n";
    cout << setw(20) << "Notepad" << "Text editor with autosave.\n";
    cout << setw(20) << "Clock" << "Displays current time, updates every second.\n";
    cout << setw(20) << "Calendar" << "Shows current date and day of week.\n";
    cout << setw(20) << "Create File" << "Creates a new file.\n";
    cout << setw(20) << "Delete File" << "Deletes a file.\n";
    cout << setw(20) << "Copy File" << "Copies a file.\n";
    cout << setw(20) << "File Info" << "Displays file metadata.\n";
    cout << setw(20) << "Move File" << "Moves a file.\n";
    cout << setw(20) << "Task Manager" << "Lists and kills running tasks.\n";
    cout << setw(20) << "Music Player" << "Plays a simulated tune.\n";
    cout << setw(20) << "Number Guessing" << "Guess a random number.\n";
    cout << setw(20) << "Print File" << "Prints file contents with delay.\n";
    cout << setw(20) << "Instruction Guide" << "Shows this guide.\n";
    cout << setw(20) << "Dice Roller" << "Rolls a D6 or D20 die.\n";
    cout << "\nCommands:\n";
    cout << "k: Enter kernel mode\n";
    cout << "s: Shutdown VERTEX\n";
    cout << "q: Quit any task\n";
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    return 0;
}
