#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct VectorSinConstants_SSE_V06
{
	XMVECTOR inv_two_pi;		// 16 bytes

	float pi;					//  4 bytes
	float two_pi;				//  4 bytes
	float sign_bit;				//  4 bytes
	float half_pi;				//  4 bytes

	float coefficients[6];		// 24 bytes

	// Total struct size:		   56 bytes (1 cache lines)
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern VectorSinConstants_SSE_V06 VECTOR_SIN_CONSTANTS_SSE_V06;

// V06 uses a few float constants to reduce the total size to 1 cache line
inline XMVECTOR XM_CALLCONV XMVectorSin_SSE_V06(FXMVECTOR V)
{
	// 11-degree minimax approximation
	// Force the value within the bounds of pi
	XMVECTOR quotient = _mm_mul_ps(V, VECTOR_SIN_CONSTANTS_SSE_V06.inv_two_pi);
	quotient = _mm_round_ps(quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
	quotient = _mm_mul_ps(quotient, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.two_pi));
	XMVECTOR x = _mm_sub_ps(V, quotient);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x).
	XMVECTOR sign = _mm_and_ps(x, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.sign_bit));
	XMVECTOR c = _mm_or_ps(_mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.pi), sign);  // pi when x >= 0, -pi when x < 0
	XMVECTOR absx = _mm_andnot_ps(sign, x);  // |x|
	XMVECTOR rflx = _mm_sub_ps(c, x);
	XMVECTOR comp = _mm_cmple_ps(absx, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.half_pi));
	XMVECTOR select0 = _mm_and_ps(comp, x);
	XMVECTOR select1 = _mm_andnot_ps(comp, rflx);
	x = _mm_or_ps(select0, select1);

	XMVECTOR x2 = _mm_mul_ps(x, x);

	// Compute polynomial approximation
	XMVECTOR Result = _mm_mul_ps(x2, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.coefficients[0]));
	Result = _mm_add_ps(Result, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.coefficients[1]));
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.coefficients[2]));
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.coefficients[3]));
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.coefficients[4]));
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V06.coefficients[5]));
	Result = _mm_mul_ps(Result, x);
	return Result;
}
