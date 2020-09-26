#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

void save_pid(char path[]) {
    ofstream file(path);
    file << getpid();
    file.close();
}

int main(int argc, char *argv[])
{
    const int pid = fork();

    switch(pid)
    {
        case -1 : {
            cout<<"Error while process fork";
            break;
        }
        case 0 : {
            save_pid("/home/box/pid_child");
            signal(SIGTERM, SIG_DFL);
            break;
        }
        default : {
            save_pid("/home/box/pid_parent");
            int status;
            waitpid(pid, &status, WUNTRACED);
            break;
        }
    }

    pause();
    return 0;
}