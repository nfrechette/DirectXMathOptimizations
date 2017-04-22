#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct ScalarSinConstants_V06
{
	float half;					//  4 bytes
	float pi;					//  4 bytes
	float neg_pi;				//  4 bytes
	float two_pi;				//  4 bytes
	float inv_two_pi;			//  4 bytes
	float half_pi;				//  4 bytes
	float neg_half_pi;			//  4 bytes

	float coefficients[6];		// 24 bytes

	// Total struct size:		   52 bytes
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern ScalarSinConstants_V06 SCALAR_SIN_CONSTANTS_V06;

// V06 is identical to V04 except that we allow the function to inline
// Sadly it fails to inline
// It uses: 5 XMM registers, 34 instructions
inline float XMScalarSin_V06(float Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = Value * SCALAR_SIN_CONSTANTS_V06.inv_two_pi;
	if (Value >= 0.0f)
	{
		quotient += SCALAR_SIN_CONSTANTS_V06.half;
	}
	else
	{
		quotient -= SCALAR_SIN_CONSTANTS_V06.half;
	}
	quotient = (float)((int)quotient);

	float y = Value - (quotient * SCALAR_SIN_CONSTANTS_V06.two_pi);

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	if (y > SCALAR_SIN_CONSTANTS_V06.half_pi)
	{
		y = SCALAR_SIN_CONSTANTS_V06.pi - y;
	}
	else if (!(SCALAR_SIN_CONSTANTS_V06.neg_half_pi < y))
	{
		y = SCALAR_SIN_CONSTANTS_V06.neg_pi - y;
	}

	// 11-degree minimax approximation
	float y2 = y * y;
	float result = y2 * SCALAR_SIN_CONSTANTS_V06.coefficients[0];
	result += SCALAR_SIN_CONSTANTS_V06.coefficients[1];
	result *= y2;
	result -= SCALAR_SIN_CONSTANTS_V06.coefficients[2];
	result *= y2;
	result += SCALAR_SIN_CONSTANTS_V06.coefficients[3];
	result *= y2;
	result -= SCALAR_SIN_CONSTANTS_V06.coefficients[4];
	result *= y2;
	result += SCALAR_SIN_CONSTANTS_V06.coefficients[5];
	return result * y;
}
