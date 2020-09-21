#include <iostream>

using namespace std;

class StringPointer
{

private:
    string *ptr;
    bool alloced = false;

public:
    operator string *() { return ptr; };

    string *operator->() { return ptr; };

    StringPointer(string *pointer) : ptr(pointer)
    {
        if (pointer == NULL)
        {
            cerr << "Pointer was initialized as NULL" << endl;
            ptr = new string();
            alloced = true;
        }
    };

    ~StringPointer()
    {
        if (alloced)
        {
            delete ptr;
        }
    }
};
