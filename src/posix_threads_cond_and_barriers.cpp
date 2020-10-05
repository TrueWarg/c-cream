#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <fstream>

// just random calling func (it must not work)
void* stub_handler(void* arg)
{
    return 0;
}

void run(void *arg)
{
    pthread_t thread;
    pthread_create(&thread, 0, stub_handler, arg);
    pthread_detach(thread);
}

int main(int argc, char *argv[])
{
    std::ofstream file("/home/box/main.pid");
    file << getpid();
    file.close();

    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mut;
	pthread_mutex_init(&mut, 0);
	pthread_mutex_lock(&mut);
    pthread_cond_wait(&cond, &mut);
    run(&cond);

    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, 0, 2);
    pthread_barrier_wait(&barrier);
    run(&barrier);
    
    // add unlocks if needed

    return 0;
}