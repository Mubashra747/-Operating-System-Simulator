#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <unistd.h>
using namespace std;

bool playing = true;

void* play_music(void* arg) {
    for (int i = 0; i < 10 && playing; ++i) {
        cout << "\a"; // Beep
        cout << "Playing tune " << i + 1 << "/10\n" << flush;
        sleep(2);
    }
    return nullptr;
}

int main() {
    pthread_t music_thread;
    pthread_create(&music_thread, NULL, play_music, NULL);
    cout << "**************************************\n";
    cout << "          Music Player\n";
    cout << "**************************************\n";
    cout << "Press 'q' to quit\n";
    char quit;
    while (cin >> quit && quit != 'q');
    playing = false;
    pthread_join(music_thread, NULL);
    return 0;
}
