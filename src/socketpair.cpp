#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    const int pid = fork();
    int sv[2];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) {
        cout << "Error while socket creation";
        return 2;
    }

    switch (pid) {
        case -1: {
            cout << "Error while process fork";
            return 2;
        }
        case 0: {
            // child process
            close(sv[0]);
            break;
        }
        default: {
            // parent proc
            close(sv[1]);
            break;
        }
    }
    pause();
    return 0;
}