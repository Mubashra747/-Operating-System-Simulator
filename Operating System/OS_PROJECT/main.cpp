#include <iostream>
#include <iomanip>
#include <vector>
#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <fstream>
using namespace std;

// Resource struct
struct Resource {
    size_t ram_total, ram_used;
    size_t hdd_total, hdd_used;
    int processors;
};

// Task struct for queue
struct Task {
    pid_t pid; // Now stores gnome-terminal PID
    string name;
    size_t ram, hdd;
    int priority; // 1=interactive, 2=background, 3=auto
};

// Global resources and queue
Resource resources;
vector<Task> ready_queue;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t cout_mutex = PTHREAD_MUTEX_INITIALIZER;
bool shutdown = false;

// Update tasks.txt with current tasks
void update_task_file(const vector<Task>& ready_queue) {
    ofstream file("tasks.txt");
    for (const auto& task : ready_queue) {
        file << task.pid << "," << task.name << "," << task.ram << "," << task.hdd << "," << task.priority << "\n";
    }
    file.close();
}

// Display VERTEX boot
void boot_os() {
    pthread_mutex_lock(&cout_mutex);
    cout << "**************************************\n";
    cout << "        Welcome to VERTEX v1.0\n";
    cout << "**************************************\n";
    cout << "Booting...\n";
    pthread_mutex_unlock(&cout_mutex);
    sleep(3);
    pthread_mutex_lock(&cout_mutex);
    cout << "Boot complete!\n" << flush;
    pthread_mutex_unlock(&cout_mutex);
}

// Prompt for resources with validation
void init_resources() {
    size_t ram, hdd;
    int processors;
    do {
        pthread_mutex_lock(&cout_mutex);
        cout << "Enter RAM (MB, min 10): ";
        pthread_mutex_unlock(&cout_mutex);
        cin >> ram;
        if (cin.fail() || ram < 10) {
            pthread_mutex_lock(&cout_mutex);
            cout << "Error: RAM must be at least 10 MB.\n";
            pthread_mutex_unlock(&cout_mutex);
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (ram < 10);
    resources.ram_total = ram;
    resources.ram_used = 0;

    do {
        pthread_mutex_lock(&cout_mutex);
        cout << "Enter Hard Drive (MB, min 50): ";
        pthread_mutex_unlock(&cout_mutex);
        cin >> hdd;
        if (cin.fail() || hdd < 50) {
            pthread_mutex_lock(&cout_mutex);
            cout << "Error: HDD must be at least 50 MB.\n";
            pthread_mutex_unlock(&cout_mutex);
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (hdd < 50);
    resources.hdd_total = hdd;
    resources.hdd_used = 0;

    do {
        pthread_mutex_lock(&cout_mutex);
        cout << "Enter Number of Processors (min 1): ";
        pthread_mutex_unlock(&cout_mutex);
        cin >> processors;
        if (cin.fail() || processors < 1) {
            pthread_mutex_lock(&cout_mutex);
            cout << "Error: At least 1 processor required.\n";
            pthread_mutex_unlock(&cout_mutex);
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (processors < 1);
    resources.processors = processors;
    cin.ignore(10000, '\n');
}

// Check if enough resources are available for a task
bool check_resources(size_t ram, size_t hdd) {
    pthread_mutex_lock(&queue_mutex);
    bool available = (resources.ram_used + ram <= resources.ram_total) &&
                     (resources.hdd_used + hdd <= resources.hdd_total);
    if (available) {
        resources.ram_used += ram;
        resources.hdd_used += hdd;
    }
    pthread_mutex_unlock(&queue_mutex);
    return available;
}

// Release resources after a task is finished
void release_resources(size_t ram, size_t hdd) {
    pthread_mutex_lock(&queue_mutex);
    resources.ram_used -= ram;
    resources.hdd_used -= hdd;
    pthread_mutex_unlock(&queue_mutex);
}

// Launch task in new gnome-terminal
bool launch_task(const string& task_name, size_t ram, size_t hdd, int priority) {
    if (!check_resources(ram, hdd)) {
        pthread_mutex_lock(&cout_mutex);
        cout << "Insufficient resources for " << task_name << "! Try increasing RAM or HDD.\n" << flush;
        pthread_mutex_unlock(&cout_mutex);
        return false;
    }
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: launch in gnome-terminal
        string full_command = "./" + task_name;
        execlp("gnome-terminal", "gnome-terminal", "--", "bash", "-c", (full_command + "; exit").c_str(), (char*)NULL);
        pthread_mutex_lock(&cout_mutex);
        cerr << "Error launching " << task_name << ": execlp failed\n" << flush;
        pthread_mutex_unlock(&cout_mutex);
        exit(1);
    } else if (pid > 0) {
        pthread_mutex_lock(&queue_mutex);
        ready_queue.push_back({pid, task_name, ram, hdd, priority});
        update_task_file(ready_queue);
        pthread_cond_signal(&queue_cond);
        pthread_mutex_unlock(&queue_mutex);
        return true;
    } else {
        pthread_mutex_lock(&cout_mutex);
        cout << "Error forking for " << task_name << "\n" << flush;
        pthread_mutex_unlock(&cout_mutex);
        release_resources(ram, hdd);
        return false;
    }
}

// Display menu
void display_menu() {
    cout << "**************************************\n";
    cout << "             VERTEX OS\n";
    cout << "**************************************\n";
    cout << "Resources: " << resources.ram_used << "/" << resources.ram_total << " MB RAM, ";
    cout << resources.hdd_used << "/" << resources.hdd_total << " MB HDD, ";
    cout << resources.processors << " Processors\n";
    cout << "1. Calculator\n2. Notepad\n3. Clock\n4. Calendar\n5. Create File\n";
    cout << "6. Delete File\n7. Copy File\n8. File Info\n9. Move File\n10. Task Manager\n";
    cout << "11. Music Player\n12. Number Guessing\n13. Print File\n14. Instruction Guide\n";
    cout << "15. Dice Roller\nk. Kernel Mode\ns. Shutdown\n";
    cout << "Enter choice: ";
}

int main() {
    boot_os();
    init_resources();

    while (!shutdown) {
        pthread_mutex_lock(&cout_mutex);
        display_menu();
        cout << flush;
        pthread_mutex_unlock(&cout_mutex);

        string choice;
        pthread_mutex_lock(&cout_mutex);
        getline(cin, choice);
        pthread_mutex_unlock(&cout_mutex);

        if (choice.empty()) continue;

        if (choice == "1") launch_task("calculator", 1, 1, 1);
        else if (choice == "2") launch_task("notepad", 2, 5, 1);
        else if (choice == "3") launch_task("clock", 1, 0, 3);
        else if (choice == "4") launch_task("calendar", 1, 0, 3);
        else if (choice == "5") launch_task("file_create", 1, 1, 2);
        else if (choice == "6") launch_task("file_delete", 1, 0, 2);
        else if (choice == "7") launch_task("file_copy", 1, 2, 2);
        else if (choice == "8") launch_task("file_info", 1, 0, 2);
        else if (choice == "9") launch_task("file_move", 1, 1, 2);
        else if (choice == "10") launch_task("task_manager", 1, 0, 1);
        else if (choice == "11") launch_task("music_player", 2, 2, 1);
        else if (choice == "12") launch_task("number_guessing", 1, 0, 3);
        else if (choice == "13") launch_task("file_print", 1, 1, 2);
        else if (choice == "14") launch_task("instruction_guide", 1, 0, 3);
        else if (choice == "15") launch_task("dice_roller", 1, 0, 3);
        else if (choice == "s") shutdown = true;
    }
    return 0;
}
