#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// This is the original DirectXMath implementation, as is, for SSE only
inline float XMScalarCos_Ref(float Value)
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

	// Map y to [-pi/2,pi/2] with cos(y) = sign*cos(x).
	float sign;
	if (y > XM_PIDIV2)
	{
		y = XM_PI - y;
		sign = -1.0f;
	}
	else if (y < -XM_PIDIV2)
	{
		y = -XM_PI - y;
		sign = -1.0f;
	}
	else
	{
		sign = +1.0f;
	}

	// 10-degree minimax approximation
	float y2 = y*y;
	float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
	return sign*p;
}
