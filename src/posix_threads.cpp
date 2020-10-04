#include <pthread.h>
#include <stdio.h>
#include <fstream>

void some_func() {
    while(true) {
        // nothing to do
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    const int pid  = pthread_create(&thread, NULL, some_func, NULL);
    
    std::ofstream file("/home/box/main.pid");
    file << pid;
    file.close();

    pthread_join(thread,NULL)
    return 0;
}