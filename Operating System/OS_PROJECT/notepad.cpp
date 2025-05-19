#include <iostream>
#include <iomanip>
#include <vector>
#include <mutex>
#include <pthread.h>
#include <unistd.h>
using namespace std;

vector<string> lines;
mutex lines_mutex;
bool running = true;

void* autosave(void* arg) {
    while (running) {
        sleep(5);
        lines_mutex.lock();
        FILE* fp = fopen("data/notepad.txt", "w");
        for (const auto& line : lines) {
            fprintf(fp, "%s\n", line.c_str());
        }
        fclose(fp);
        lines_mutex.unlock();
    }
    return nullptr;
}

int main() {
    pthread_t save_thread;
    pthread_create(&save_thread, NULL, autosave, NULL);
    string input;
    cout << "**************************************\n";
    cout << "             Notepad\n";
    cout << "**************************************\n";
    cout << "Enter text (one line at a time, 'q' to quit):\n";
    while (true) {
        getline(cin, input);
        if (input == "q") break;
        lines_mutex.lock();
        lines.push_back(input);
        lines_mutex.unlock();
    }
    running = false;
    pthread_join(save_thread, NULL);
    return 0;
}
