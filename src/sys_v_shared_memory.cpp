#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    const int memory_size = 1024 * 1024;
    const key_t key = ftok("/tmp/mem.temp", 1);
    const int shmid = shmget(key, memory_size, IPC_CREAT | 0666);
    char *attached = (char *)shmat(shmid, 0, 0);
    for (int i = 0; i < memory_size; i++)
    {
        attached[i] = 42;
    }
    // detach from shared memory usinng 'shmdt(attached)' if it's needed
    return 0;
}