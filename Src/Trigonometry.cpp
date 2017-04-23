#include "stdafx.h"
#include "ScalarSin.h"

#include <DirectXMath.h>

#include <thread>
#include <windows.h>

#include <conio.h>

void ProfileTrigonometry()
{
	const __int32 mask = 1 << 4;
	SetThreadAffinityMask(GetCurrentThread(), mask);

	//constexpr __int32 num_samples = 100;
	constexpr __int32 num_samples = 10;

	constexpr __int32 num_iterations = 100000 * 2;
	//constexpr __int32 num_iterations = 1000;

	constexpr __int32 random_seed = 304;

	ProfileScalarSin(random_seed, num_samples, num_iterations);
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
