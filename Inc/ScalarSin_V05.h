#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct ScalarSinConstants_V05
{
	float half;					//  4 bytes
	float neg_half;				//  4 bytes
	float pi;					//  4 bytes
	float neg_pi;				//  4 bytes
	float two_pi;				//  4 bytes
	float inv_two_pi;			//  4 bytes
	float half_pi;				//  4 bytes
	float neg_half_pi;			//  4 bytes

	float coefficients[6];		// 24 bytes

	// Total struct size:		   56 bytes
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern ScalarSinConstants_V05 SCALAR_SIN_CONSTANTS_V05;

// V05 is the best I could do with C++ scalar math
// Nearly everything uses as few registers as possible by leveraging instructions that
// can load constants directly from memory.
// All constants are packed in the same cache line
// A single xor instruction is generated for no reason when we convert/floor quotient
// to zero out the XMM.yzw components but it isn't strictly necessary
// Also maybe we can use the SSE round instruction?
// It uses: 5 XMM registers, 34 instructions
__declspec(noinline) float XMScalarSin_V05(float Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = Value * SCALAR_SIN_CONSTANTS_V05.inv_two_pi;
	const float rounding_offset = Value >= 0.0f ? SCALAR_SIN_CONSTANTS_V05.half : SCALAR_SIN_CONSTANTS_V05.neg_half;
	quotient = float(int(quotient + rounding_offset));

	float y = Value - (quotient * SCALAR_SIN_CONSTANTS_V05.two_pi);

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	if (y > SCALAR_SIN_CONSTANTS_V05.half_pi)
	{
		y = SCALAR_SIN_CONSTANTS_V05.pi - y;
	}
	else if (!(SCALAR_SIN_CONSTANTS_V05.neg_half_pi < y))
	{
		y = SCALAR_SIN_CONSTANTS_V05.neg_pi - y;
	}

	// 11-degree minimax approximation
	float y2 = y * y;
	float result = y2 * SCALAR_SIN_CONSTANTS_V05.coefficients[0];
	result += SCALAR_SIN_CONSTANTS_V05.coefficients[1];
	result *= y2;
	result -= SCALAR_SIN_CONSTANTS_V05.coefficients[2];
	result *= y2;
	result += SCALAR_SIN_CONSTANTS_V05.coefficients[3];
	result *= y2;
	result -= SCALAR_SIN_CONSTANTS_V05.coefficients[4];
	result *= y2;
	result += SCALAR_SIN_CONSTANTS_V05.coefficients[5];
	return result * y;
}
