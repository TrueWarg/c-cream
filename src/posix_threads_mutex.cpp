#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <fstream>

// just random calling func (it may not work)
void* handler(void* arg)
{
    return 0;
}

void run(void *arg)
{
    pthread_t thread;
    pthread_create(&thread, 0, handler, arg);
    pthread_detach(thread);
}

void mutex()
{
    pthread_mutex_t mut;
    pthread_mutex_init(&mut, 0);
    pthread_mutex_lock(&mut);
    run(&mut);
}

void spin()
{
    pthread_spinlock_t spin;
    pthread_spin_init(&spin, 0);
    pthread_spin_lock(&spin);
    run((void *)&spin);
}

void wlock() {
    pthread_rwlock_t rwlock;
	pthread_rwlock_init(&rwlock, 0);
	pthread_rwlock_wrlock(&rwlock);
	run(&rwlock);
}


void rlock() {
    pthread_rwlock_t rwlock;
	pthread_rwlock_init(&rwlock, 0);
	pthread_rwlock_rdlock(&rwlock);
	run(&rwlock);
}

int main(int argc, char *argv[])
{
    std::ofstream file("/home/box/main.pid");
    file << getpid();
    file.close();

    mutex();
    spin();
    wlock();
    rlock();

    // add unlocks if needed

    return 0;
}