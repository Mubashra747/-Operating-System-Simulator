#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <unistd.h>
using namespace std;

bool running = true;

void* update_time(void* arg) {
    while (running) {
        time_t now = time(NULL);
        cout << "Current Time: " << ctime(&now) << flush;
        sleep(1);
        cout << "\033[A\033[K"; // Move up and clear line
    }
    return nullptr;
}

int main() {
    pthread_t time_thread;
    pthread_create(&time_thread, NULL, update_time, NULL);
    cout << "**************************************\n";
    cout << "              Clock\n";
    cout << "**************************************\n";
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    running = false;
    pthread_join(time_thread, NULL);
    return 0;
}
