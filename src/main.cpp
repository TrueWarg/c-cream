#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    char memory[1048576];
    int kek = 20;
    void *suka = memory + kek;
    cout << " ede" << *static_cast<char*>(suka);
	return 0;
}
