#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>

using namespace std;

// utils string functions
vector<string> split_string(string &str, const string &delimiter = "|")
{
    vector<string> result;

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
        result.push_back(token);
    }
    // add remainder
    result.push_back(str);
    return result;
}

void trim_string(string &str)
{
    const string whitespaces(" \t\f\v\n\r");

    string::size_type pos = str.find_first_not_of(whitespaces);
    if (pos != string::npos)
    {
        str.erase(0, pos);
    }
    pos = str.find_last_not_of(whitespaces);
    if (pos != string::npos)
    {
        str.erase(pos + 1);
    }
}

void parse_command(string &command, string &name, string &args)
{
    trim_string(command);
    string::size_type pos = command.find_first_of(' ');
    if (pos != string::npos)
    {
        name = command.substr(0, pos);
        args = command.substr(pos + 1, command.length() - pos - 1);
    }
    else
    {
        name = command;
        args = "";
    }
}

void exec_command(string &command)
{
    string name, args;
    parse_command(command, name, args);
    if (args.size() > 0)
    {
        execlp(name.c_str(), name.c_str(), args.c_str(), NULL);
    }
    else
    {
        execlp(name.c_str(), name.c_str(), NULL);
    }
}

// std('command line')
// process 1 (first command):
// init stdin ---|pipe_1|---pfd_1[1] ~ stdout
// process 2 (forked child):
// std ---|pipe_1|---pfd_1[1]---pfd_1[0]---|pipe2|---pfd_2[1] ~ stdout
// .............................................................................................
// process n (last command):
// std ---|pipe_1|---pfd_1[1]---pfd_1[0]---|pipe2|---pfd_2[1]---...---|pipe_n-1|---pfd_n-1[1]---pdf_n-1[0]---df ~ stdout (in file)                     
void exec_command_seq(vector<string> &commands)
{
    const int commands_size = commands.size();

    for (int i = 0; i < commands_size; i++)
    {
        int pfd[2];
        pipe(pfd);

        if (!fork())
        {
            close(STDOUT_FILENO);
            dup2(pfd[1], STDOUT_FILENO);
            close(pfd[1]);
            close(pfd[0]);
            exec_command(commands[i]);
            exit(0);
        }

        close(STDIN_FILENO);
        dup2(pfd[0], STDIN_FILENO);

        if (i == commands_size - 1) {
            int fd = open("/home/box/result.out", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            exec_command(commands[i]);
        }

        close(pfd[0]);
        close(pfd[1]);
    }
}

int main()
{
    const int buffer_size = 1024;
    char buffer[buffer_size];
    ssize_t size = read(STDIN_FILENO, buffer, buffer_size);
    if (size > 0)
    {
        buffer[size] = '\0';
        string command_line = buffer;
        vector<string> commands = split_string(command_line, "|");
        exec_command_seq(commands);
    }

    return 0;
}