#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main(int argc, const char *argv[])
{
    const char *input_path = "/home/box/in.fifo";
    const char *output_path = "/home/box/out.fifo";

    mkfifo(input_path, 0666);
    mkfifo(output_path, 0666);

    const int input_fd = open(input_path, O_RDONLY);
    const int output_fd = open(output_path, O_WRONLY);

    char buffer[1024];
    size_t read_length = 0;

    while ((read_length = read(input_fd, buffer, sizeof(buffer))) > 0)
        write(output_fd, buffer, read_length);

    return 0;
}
