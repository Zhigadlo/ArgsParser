#include <iostream>
int main(int argC, const char ** argV) 
{
	for (int i = 0; i < argC; i++)
	{
		std::cout << argV[i] << std::endl;
	}
}