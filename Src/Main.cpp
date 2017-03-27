// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <random>

#include "MatrixMultiply.h"

int main()
{
	ProfileMatrixMultiply();

	if (IsDebuggerPresent())
	{
		printf("Press any key to continue...\n");
		while (_kbhit() == 0);
	}

	return 0;
}

