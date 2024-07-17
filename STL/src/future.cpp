#include <iostream>
#include <future>
#include <thread>
#include <unistd.h>

#include "utils.h"

using namespace std;

void firstThread () {
    // createFile("firstThread.txt");
    while (true) {
        sleep(1);
        cout << __func__ << " runs in thread at " << this_thread::get_id() << endl;
    }
}

int main()
{
    cout << __func__ << " runs in thread at " << this_thread::get_id() << endl;
    thread t(firstThread);
    sleep(1.5);
    cout << "main\n";
    t.join();
    cout << "return" << endl;
    return 0;
}