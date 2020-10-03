#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[])
{
    
    const char* key_path = "/tmp/msg.temp";
    struct { long mtype;char mtext[80]; } message;

    if (creat(key_path, 0666) == -1) {
        cout << "Error while key file generation" << endl;
        return -1;
    }

    const key_t key = ftok(key_path, 1);

    const int message_id = msgget(key, IPC_CREAT | 0666);
    if (message_id == -1) {
        cout << "Error while message receiving" << endl;
        return -1;
    }

    const int recieved_length = msgrcv(message_id, &message, sizeof(message), 0, 0);

    const int output_fd = open("/home/box/message.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (output_fd == -1) {
        cout << "Error while opening output file" << endl;
        return -1;
    }

    write(output_fd, message.mtext, recieved_length);

    return 0;
}