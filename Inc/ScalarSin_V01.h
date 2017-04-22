#pragma once

#include <DirectXMath.h>

using namespace DirectX;

constexpr float ROUNDING_OFFSET_V01[] = { -0.5f, 0.5f };
constexpr float WRAPPING_OFFSET_V01[] = { 0.0f, XM_PI, -XM_PI };
constexpr float WRAPPING_SCALE_V01[] = { 1.0f, -1.0f, -1.0f };

// V01 tries to remove the first and second branches
__declspec(noinline) float XMScalarSin_V01(const float Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = XM_1DIV2PI * Value;
	quotient = (float)((int)(quotient + ROUNDING_OFFSET_V01[Value >= 0.0f]));

	float y = Value - XM_2PI * quotient;

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	// range_index == 0 -> y >= -XM_PIDIV2 && y <= XM_PIDIV2
	//     y = y
	//     y = 1 * (y + 0)
	// range_index == 1 -> y < -XM_PIDIV2
	//     y = -y - XM_PI
	//     y = -1 * (y + XM_PI)
	// range_index == 2 -> y > XM_PIDIV2
	//     y = -y + XM_PI
	//     y = -1 * (y - XM_PI)
	//
	// y is rarely outside the [-pi/2,pi/2] range, the branches are nearly constant
	// removing the branches is slower
	unsigned int range_index = ((y > XM_PIDIV2) << 1) | (y < -XM_PIDIV2);
	y = (y + WRAPPING_OFFSET_V01[range_index]) * WRAPPING_SCALE_V01[range_index];

	// 11-degree minimax approximation
	float y2 = y * y;
	return (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
}
