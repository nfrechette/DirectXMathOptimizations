#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct ScalarSinConstants_SSE_V10
{
	float pi;					//  4 bytes
	float neg_pi;				//  4 bytes
	float two_pi;				//  4 bytes
	float inv_two_pi;			//  4 bytes
	float half_pi;				//  4 bytes
	float neg_half_pi;			//  4 bytes

	float coefficients[6];		// 24 bytes

	// Total struct size:		   48 bytes
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern ScalarSinConstants_SSE_V10 SCALAR_SIN_CONSTANTS_SSE_V10;

// V10 is identical to V09 except that we allow the function to inline and we align/pack all the constants
// It inlines!
inline float XMScalarSin_SSE_V10(const float Value)
{
	const XMVECTOR value_v = _mm_set_ps1(Value);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	XMVECTOR quotient = _mm_mul_ss(value_v, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_SSE_V10.inv_two_pi);
	quotient = _mm_round_ss(quotient, quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);

	XMVECTOR y = _mm_sub_ss(value_v, _mm_mul_ss(quotient, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_SSE_V10.two_pi));
	if (_mm_comigt_ss(y, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_SSE_V10.half_pi))
	{
		y = _mm_sub_ss(*(XMVECTOR*)&SCALAR_SIN_CONSTANTS_SSE_V10.pi, y);	// 1 cmp, 1 sub, 3 mov, 2 jmp = 7 instructions
	}
	else if (!_mm_comile_ss(*(XMVECTOR*)&SCALAR_SIN_CONSTANTS_SSE_V10.neg_half_pi, y))
	{
		y = _mm_sub_ss(*(XMVECTOR*)&SCALAR_SIN_CONSTANTS_SSE_V10.neg_pi, y);	// 2 cmp, 1 sub, 3 mov, 2 jmp = 8 instructions
	}
	else
	{
		// 2 cmp, 2 jmp, 1 mov = 5 instructions
	}

	float y_scalar = _mm_cvtss_f32(y);

	// 11-degree minimax approximation
	float y2 = y_scalar * y_scalar;
	float result = y2 * SCALAR_SIN_CONSTANTS_SSE_V10.coefficients[0];
	result += SCALAR_SIN_CONSTANTS_SSE_V10.coefficients[1];
	result *= y2;
	result -= SCALAR_SIN_CONSTANTS_SSE_V10.coefficients[2];
	result *= y2;
	result += SCALAR_SIN_CONSTANTS_SSE_V10.coefficients[3];
	result *= y2;
	result -= SCALAR_SIN_CONSTANTS_SSE_V10.coefficients[4];
	result *= y2;
	result += SCALAR_SIN_CONSTANTS_SSE_V10.coefficients[5];
	return result * y_scalar;
}
