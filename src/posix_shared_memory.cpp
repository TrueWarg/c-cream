#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    const int memory_size = 1024 * 1024;
    const key_t key = ftok("/tmp/mem.temp", 1);
    const int shmid = shm_open("/test.shm", O_CREAT | O_RDWR | O_TRUNC, 0666);
    ftruncate(shmid, memory_size);
    char *attached = (char *)mmap(0, memory_size, PROT_WRITE, MAP_SHARED, shmid, 0);

    for (int i = 0; i < memory_size; i++)
    {
        attached[i] = 13;
    }
    // detach from shared memory usinng 'munmap(attached, memory_size)' if it's needed
    // call close virtual file using 'close(shmid)'
    return 0;
}