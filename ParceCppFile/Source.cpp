// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include<iostream>
#include <string>
#include <fstream>
#include"directory.h"
int main()
{

	Directory s{ "C:\\Users\\ADMIN\\source\\repos" };
	try {
		s.Start();
	}
	catch (const std::exception& s)
	{
		std::cout << s.what() << std::endl;
	}

	std::ofstream of("input.txt");
	of << s;
    return 0;
}