#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// V04 tries to tweak the first branch differently
__declspec(noinline) float XMScalarSin_CPP_V04(float Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = XM_1DIV2PI * Value;
	if (Value >= 0.0f)
	{
		quotient += 0.5f;
	}
	else
	{
		quotient -= 0.5f;
	}
	quotient = float(int(quotient));

	float y = Value - XM_2PI * quotient;

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	if (y > XM_PIDIV2)
	{
		y = XM_PI - y;
	}
	else if (!(-XM_PIDIV2 < y))
	{
		y = -XM_PI - y;
	}

	// 11-degree minimax approximation
	float y2 = y * y;
	float result = y2 * -2.3889859e-08f;
	result += 2.7525562e-06f;
	result *= y2;
	result -= 0.00019840874f;
	result *= y2;
	result += 0.0083333310f;
	result *= y2;
	result -= 0.16666667f;
	result *= y2;
	result += 1.0f;
	return result * y;
}
