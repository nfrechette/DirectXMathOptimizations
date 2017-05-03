#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct VectorCosConstants_SSE_V00
{
	XMVECTOR inv_two_pi;		// 16 bytes
	XMVECTOR two_pi;			// 16 bytes

	XMVECTOR sign_bit;			// 16 bytes
	XMVECTOR pi;				// 16 bytes

	XMVECTOR half_pi;			// 16 bytes

	XMVECTOR one;				// 16 bytes
	XMVECTOR neg_one;			// 16 bytes

	XMVECTOR coefficients[5];	// 80 bytes

	// Total struct size:		  192 bytes (3 cache lines)
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern VectorCosConstants_SSE_V00 VECTOR_COS_CONSTANTS_SSE_V00;

// V00 uses the same tricks as VectorSin SSE V04
inline XMVECTOR XM_CALLCONV XMVectorCos_SSE_V00(FXMVECTOR V)
{
	// Map V to x in [-pi,pi].
	XMVECTOR quotient = _mm_mul_ps(V, VECTOR_COS_CONSTANTS_SSE_V00.inv_two_pi);
	quotient = _mm_round_ps(quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
	quotient = _mm_mul_ps(quotient, VECTOR_COS_CONSTANTS_SSE_V00.two_pi);
	XMVECTOR x = _mm_sub_ps(V, quotient);

	// Map in [-pi/2,pi/2] with cos(y) = sign*cos(x).
	XMVECTOR sign = _mm_and_ps(x, VECTOR_COS_CONSTANTS_SSE_V00.sign_bit);
	XMVECTOR c = _mm_or_ps(VECTOR_COS_CONSTANTS_SSE_V00.pi, sign);  // pi when x >= 0, -pi when x < 0
	XMVECTOR absx = _mm_andnot_ps(sign, x);  // |x|
	XMVECTOR rflx = _mm_sub_ps(c, x);
	XMVECTOR comp = _mm_cmple_ps(absx, VECTOR_COS_CONSTANTS_SSE_V00.half_pi);
	XMVECTOR select0 = _mm_and_ps(comp, x);
	XMVECTOR select1 = _mm_andnot_ps(comp, rflx);
	x = _mm_or_ps(select0, select1);
	select0 = _mm_and_ps(comp, VECTOR_COS_CONSTANTS_SSE_V00.one);
	select1 = _mm_andnot_ps(comp, VECTOR_COS_CONSTANTS_SSE_V00.neg_one);
	sign = _mm_or_ps(select0, select1);

	XMVECTOR x2 = _mm_mul_ps(x, x);

	// Compute polynomial approximation
	XMVECTOR Result = _mm_mul_ps(x2, VECTOR_COS_CONSTANTS_SSE_V00.coefficients[0]);
	Result = _mm_add_ps(Result, VECTOR_COS_CONSTANTS_SSE_V00.coefficients[1]);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, VECTOR_COS_CONSTANTS_SSE_V00.coefficients[2]);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, VECTOR_COS_CONSTANTS_SSE_V00.coefficients[3]);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, VECTOR_COS_CONSTANTS_SSE_V00.coefficients[4]);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, VECTOR_COS_CONSTANTS_SSE_V00.one);
	Result = _mm_mul_ps(Result, sign);
	return Result;
}
