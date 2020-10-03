#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>

int main(int argc, char *argv[])
{
	sem_open("/test.sem", O_CREAT, 0666, 66);
	return 0;
}