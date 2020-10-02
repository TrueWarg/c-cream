#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <mqueue.h>

using namespace std;

int main(int argc, char *argv[])
{
    
    const char* key_name = "/test.mq";
    char buffer[80];

    mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = 5;
	attr.mq_msgsize = 80;
	attr.mq_curmsgs = 0;

    int message_id = mq_open(key_name, O_CREAT | O_RDWR, 0666, &attr);

    int recieved_length = mq_receive(message_id, buffer, 80, 0);

    int output_fd = open("/home/box/message.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (output_fd == -1) {
        cout << "Error while opening output file" << endl;
        return -1;
    }

    write(output_fd, buffer, recieved_length);

    return 0;
}