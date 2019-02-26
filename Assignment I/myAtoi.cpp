#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define pi (acos(-1.0))
using namespace std;
int Atoi_Simulator(const char *str)
{
	int number = 0;
	bool sign_flag = false;

	if (str == NULL)                                                 //Null String
	{
		cout << "Input is Empty !";
		return 0;
	}

	while (*str == ' ')                                              //Skip All The Spaces
		str++;

	if (*str == '-' || *str == '+')                                  //Sign -> Flag Control
	{
		if (*str == '-')
			sign_flag = true;
		str++;
	}

	while (*str >= '0' && *str <= '9')                               //Transform Char Into Integer
	{
		number = number * 10 + *str - '0';
		str++;
		if (number < 0)
		{
			number = 2147483647;
			break;
		}
	}
	return number * (sign_flag ? -1 : 1);
}


int main(int argc, char const *argv[])
{
	char buffer[256];
	cout << "Enter a Number : ";
	fgets(buffer, 256, stdin);
	int Result = Atoi_Simulator(buffer);
	cout << "The Value Entered is : " << Result << endl;
	return 0;
}

