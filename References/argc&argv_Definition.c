//C Program Refenrence
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int i;
    printf("Number of Arguments = %d\n", argc);
    for (i = 0; i < argc; i++)
    {
        printf("Argument Serial Number = %d, ", i);
        printf("Argument Value = %s\n", argv[i]);
    }
    system("PAUSE");
    return 0;
}


//C++ Program Reference
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    cout << "Number of Arguments = " << argc << endl;
    for (int i = 0; i < argc; i++)
    {
        cout << "Argument Serial Number = " << i << ", ";
        cout << "Argument Value = " << argv[i] << endl;
    }
    system("PAUSE");
    return 0;
}




//Command Line : < test.exe 2 Hello World
//Result : Number of Arguments = 4
//         Argument Serial Number = 0, Argument Value = test.exe
//         Argument Serial Number = 1, Argument Value = 2
//         Argument Serial Number = 2, Argument Value = Hello
//         Argument Serial Number = 3, Argument Value = World
