#include <signal.h>
#include <unistd.h>
#include <fstream>

int main(int argc, char *argv[])
{
    std::ofstream file("/home/box/pid");
    file << getpid();
    file.close();

    signal(SIGTERM, SIG_IGN);
    signal(SIGINT, SIG_IGN);

    pause();
    return 0;
}