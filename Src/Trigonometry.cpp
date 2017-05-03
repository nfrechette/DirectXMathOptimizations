#include "stdafx.h"
#include "ScalarSin\ScalarSin.h"
#include "VectorSin\VectorSin.h"
#include "ScalarCos\ScalarCos.h"
#include "VectorCos\VectorCos.h"

#include <thread>
#include <windows.h>

#include <conio.h>

void ProfileTrigonometry()
{
	const __int32 mask = 1 << 4;
	SetThreadAffinityMask(GetCurrentThread(), mask);

	ProfileScalarSin();
	ProfileVectorSin();

	ProfileScalarCos();
	ProfileVectorCos();
}

int main()
{
	ProfileTrigonometry();

	if (IsDebuggerPresent())
	{
		printf("Press any key to continue...\n");
		while (_kbhit() == 0);
	}

	return 0;
}
