#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// This is the original DirectXMath implementation, as is, for SSE only
// It uses: 5 XMM registers, 36 instructions
inline float XMScalarSin_Ref(float Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = XM_1DIV2PI*Value;
	if (Value >= 0.0f)
	{
		quotient = (float)((int)(quotient + 0.5f));
	}
	else
	{
		quotient = (float)((int)(quotient - 0.5f));
	}
	float y = Value - XM_2PI*quotient;

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	if (y > XM_PIDIV2)
	{
		y = XM_PI - y;
	}
	else if (y < -XM_PIDIV2)
	{
		y = -XM_PI - y;
	}

	// 11-degree minimax approximation
	float y2 = y * y;
	return (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
}
