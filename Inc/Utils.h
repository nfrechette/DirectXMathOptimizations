#pragma once

#include <windows.h>
#include <random>

inline float DegToRad(const float input)
{
	return input / 360.0f * XM_2PI;
}

inline bool EnsureMatrixEqual(CXMMATRIX m1, CXMMATRIX m2)
{
	if (memcmp(&m1, &m2, sizeof(XMMATRIX)) != 0)
	{
		abort();
		return false;
	}

	return true;
}

extern XMMATRIX GenerateRandomMatrix(std::default_random_engine& re);

template<class Lambda>
__forceinline LONGLONG Measure(const __int32 num_iterations, Lambda function)
{
	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);

	for (__int32 i = 0; i < num_iterations; ++i)
	{
		function();
	}

	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);

	LONGLONG ticks = end.QuadPart - start.QuadPart;
	return ticks;
}

inline double TicksToMS(const LONGLONG ticks)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	double elapsed_seconds = static_cast<double>(ticks) / static_cast<double>(freq.QuadPart);
	double elapsed_ms = elapsed_seconds * 1000.0;
	return elapsed_ms;
}
