#pragma once

#include <windows.h>
#include <random>

#include <DirectXMath.h>

inline float DegToRad(const float input)
{
	return input / 360.0f * DirectX::XM_2PI;
}

inline bool EnsureMatrixEqual(DirectX::CXMMATRIX m1, DirectX::CXMMATRIX m2)
{
	if (memcmp(&m1, &m2, sizeof(DirectX::XMMATRIX)) != 0)
	{
		abort();
		return false;
	}

	return true;
}

inline bool IsFloatEqual(const float v1, const float v2)
{
	const bool inputs_equal = memcmp(&v1, &v2, sizeof(float)) == 0;
	const bool both_zero = v1 == 0.0f && v2 == 0.0f;
	return inputs_equal || both_zero;
}

inline bool EnsureFloatEqual(const float v1, const float v2)
{
	if (!IsFloatEqual(v1, v2))
	{
		abort();
		return false;
	}

	return true;
}

inline bool XM_CALLCONV EnsureVectorEqual(const DirectX::XMVECTOR v1, const DirectX::XMVECTOR v2)
{
	if (!IsFloatEqual(*((float*)&v1 + 0), *((float*)&v2 + 0))
		|| !IsFloatEqual(*((float*)&v1 + 1), *((float*)&v2 + 1))
		|| !IsFloatEqual(*((float*)&v1 + 2), *((float*)&v2 + 2))
		|| !IsFloatEqual(*((float*)&v1 + 3), *((float*)&v2 + 3)))
	{
		abort();
		return false;
	}

	return true;
}

inline bool EnsureFloatApproxEqual(const float v1, const float v2, const double threshold)
{
	const double delta_abs = fabs(double(v1) - double(v2));
	if (delta_abs > threshold)
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
