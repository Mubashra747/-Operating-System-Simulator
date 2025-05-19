#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <signal.h>
#include <unistd.h>
#include <string>
using namespace std;

// Task struct to match main.cpp
struct Task {
    pid_t pid;
    string name;
    size_t ram;
    size_t hdd;
    int priority;
    int state; // 0=Ready, 1=Running, 2=Blocked
    int turnaround_time;
};

// Close current terminal on exit
void close_terminal() {
    kill(getpid(), SIGTERM);
}

// Read tasks from tasks.txt
vector<Task> read_tasks() {
    vector<Task> tasks;
    ifstream file("tasks.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string pid_str, name, ram_str, hdd_str, priority_str, state_str, tt_str;
        getline(ss, pid_str, ',');
        getline(ss, name, ',');
        getline(ss, ram_str, ',');
        getline(ss, hdd_str, ',');
        getline(ss, priority_str, ',');
        getline(ss, state_str, ',');
        getline(ss, tt_str, ',');
        Task task;
        task.pid = stoi(pid_str);
        task.name = name;
        task.ram = stoul(ram_str);
        task.hdd = stoul(hdd_str);
        task.priority = stoi(priority_str);
        task.state = stoi(state_str);
        task.turnaround_time = stoi(tt_str);
        tasks.push_back(task);
    }
    file.close();
    return tasks;
}

// Display tasks in a formatted table
void display_tasks(const vector<Task>& tasks) {
    cout << "\nNEXUS Task Manager\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << left << setw(10) << "PID"
         << setw(20) << "Name"
         << setw(10) << "RAM (MB)"
         << setw(10) << "HDD (MB)"
         << setw(15) << "Priority"
         << setw(10) << "State"
         << setw(15) << "Turnaround (s)" << "\n";
    cout << "--------------------------------------------------------------------------------\n";
    size_t total_ram = 0, total_hdd = 0;
    for (const auto& task : tasks) {
        string priority_str = (task.priority == 1 ? "Interactive" : task.priority == 2 ? "Background" : "Auto");
        string state_str = (task.state == 0 ? "Ready" : task.state == 1 ? "Running" : "Blocked");
        cout << left << setw(10) << task.pid
             << setw(20) << task.name
             << setw(10) << task.ram
             << setw(10) << task.hdd
             << setw(15) << priority_str
             << setw(10) << state_str
             << setw(15) << task.turnaround_time << "\n";
        total_ram += task.ram;
        total_hdd += task.hdd;
    }
    cout << "--------------------------------------------------------------------------------\n";
    cout << "Total RAM Used: " << total_ram << " MB\n";
    cout << "Total HDD Used: " << total_hdd << " MB\n";
    cout << "Total Tasks: " << tasks.size() << "\n\n";
}

// Display menu
void display_menu() {
    cout << "Task Manager Menu:\n";
    cout << "1. Refresh Task List\n";
    cout << "2. Terminate Task\n";
    cout << "3. Minimize Task\n";
    cout << "4. Resume Task\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    atexit(close_terminal);
    cout << "NEXUS Task Manager v1.0\n";
    while (true) {
        vector<Task> tasks = read_tasks();
        display_tasks(tasks);
        display_menu();
        string choice;
        getline(cin, choice);
        if (choice == "1") {
            continue;
        } else if (choice == "2") {
            pid_t pid;
            cout << "Enter PID to terminate: ";
            cin >> pid;
            cin.ignore(10000, '\n');
            if (cin.fail()) {
                cout << "Invalid PID.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            if (kill(-pid, SIGTERM) == 0) {
                cout << "Task with PID " << pid << " terminated.\n";
            } else {
                cout << "Failed to terminate task with PID " << pid << ".\n";
            }
        } else if (choice == "3") {
            pid_t pid;
            cout << "Enter PID to minimize: ";
            cin >> pid;
            cin.ignore(10000, '\n');
            if (cin.fail()) {
                cout << "Invalid PID.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            if (kill(pid, SIGSTOP) == 0) {
                cout << "Task with PID " << pid << " minimized.\n";
            } else {
                cout << "Failed to minimize task with PID " << pid << ".\n";
            }
        } else if (choice == "4") {
            pid_t pid;
            cout << "Enter PID to resume: ";
            cin >> pid;
            cin.ignore(10000, '\n');
            if (cin.fail()) {
                cout << "Invalid PID.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            if (kill(pid, SIGCONT) == 0) {
                cout << "Task with PID " << pid << " resumed.\n";
            } else {
                cout << "Failed to resume task with PID " << pid << ".\n";
            }
        } else if (choice == "5") {
            cout << "Exiting Task Manager.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
