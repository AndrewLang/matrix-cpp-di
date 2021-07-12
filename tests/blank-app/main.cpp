// TestProgram.cpp : Defines the entry point for the console application.
//
#include "main.h"
#include <string>
#include <thread>

int main(int argc, char * argv[])
{
	int ret = 0;
	int waitMs = 100;

	if (argc > 1)
	{
		waitMs = std::stoi(argv[1]);
	}
	if (argc > 2)
	{
		ret = std::stoi(argv[2]);
	}

	if (waitMs > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(waitMs));
	}

	return ret;
}

