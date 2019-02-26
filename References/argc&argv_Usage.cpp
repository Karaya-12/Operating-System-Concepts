#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
	//Number of Arguments = 3 : Project Name(eg: Notepad.exe) / Read File(txt) / Write File(txt)
	if (argc != 3)
		throw runtime_error("Wrong Number of Arguments !");
	//Open Transformating File, argv[1] --> Read File(Waiting For Transformation File)(txt) / open_file --> Open Writing File
	if (!open_file(map_file, argv[1]))
		throw runtime_error("No Transformation File !");
	//Open Writing txt
	if (!open_file(input, argv[2]))
		throw runtime_error("No Input File !");
	return 0;
}
