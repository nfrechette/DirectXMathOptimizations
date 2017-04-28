#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct ScalarCosConstants_SSE_V00
{
	float pi;					//  4 bytes
	float neg_pi;				//  4 bytes
	float two_pi;				//  4 bytes
	float inv_two_pi;			//  4 bytes
	float half_pi;				//  4 bytes
	float neg_half_pi;			//  4 bytes
	float one;					//  4 bytes
	float neg_one;				//  4 bytes

	float coefficients[5];		// 20 bytes

	// Total struct size:		   52 bytes
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern ScalarCosConstants_SSE_V00 SCALAR_COS_CONSTANTS_SSE_V00;

// V00 uses the same tricks as ScalarSin, except we have to deal with the sign
// It sadly does not inline
inline float XMScalarCos_SSE_V00(float Value)
{
	const XMVECTOR value_v = _mm_set_ps1(Value);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	XMVECTOR quotient = _mm_mul_ss(value_v, *(XMVECTOR*)&SCALAR_COS_CONSTANTS_SSE_V00.inv_two_pi);
	quotient = _mm_round_ss(quotient, quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);

	// Map y to [-pi/2,pi/2] with cos(y) = sign*cos(x).
	XMVECTOR y = _mm_sub_ss(value_v, _mm_mul_ss(quotient, *(XMVECTOR*)&SCALAR_COS_CONSTANTS_SSE_V00.two_pi));
	float sign;
	if (_mm_comigt_ss(y, *(XMVECTOR*)&SCALAR_COS_CONSTANTS_SSE_V00.half_pi))
	{
		y = _mm_sub_ss(*(XMVECTOR*)&SCALAR_COS_CONSTANTS_SSE_V00.pi, y);
		sign = SCALAR_COS_CONSTANTS_SSE_V00.neg_one;
	}
	else if (!_mm_comile_ss(*(XMVECTOR*)&SCALAR_COS_CONSTANTS_SSE_V00.neg_half_pi, y))
	{
		y = _mm_sub_ss(*(XMVECTOR*)&SCALAR_COS_CONSTANTS_SSE_V00.neg_pi, y);
		sign = SCALAR_COS_CONSTANTS_SSE_V00.neg_one;
	}
	else
	{
		sign = SCALAR_COS_CONSTANTS_SSE_V00.one;
	}

	float y_scalar = _mm_cvtss_f32(y);

	// 10-degree minimax approximation
	float y2 = y_scalar * y_scalar;
	float result = y2 * SCALAR_COS_CONSTANTS_SSE_V00.coefficients[0];
	result += SCALAR_COS_CONSTANTS_SSE_V00.coefficients[1];
	result *= y2;
	result -= SCALAR_COS_CONSTANTS_SSE_V00.coefficients[2];
	result *= y2;
	result += SCALAR_COS_CONSTANTS_SSE_V00.coefficients[3];
	result *= y2;
	result -= SCALAR_COS_CONSTANTS_SSE_V00.coefficients[4];
	result *= y2;
	result += SCALAR_COS_CONSTANTS_SSE_V00.one;
	return result * sign;
}
