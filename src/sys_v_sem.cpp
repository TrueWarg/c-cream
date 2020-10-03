#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

union SemUnion
{
    int sem_value;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *sem_info_buf;
};

int main(int argc, char *argv[])
{
    const unsigned short sem_count = 16;
    SemUnion semun;
    const key_t sem_key = ftok("/tmp/sem.temp", 1);
    const int sem_id = semget(sem_key, sem_count, IPC_CREAT | 0666);
    unsigned short sems[sem_count];
    for (int i = 0; i < sem_count; i++)
    {
        sems[i] = i;
    }
    semun.array = sems;
    semctl(sem_id, 0, SETALL, semun);
    return 0;
}