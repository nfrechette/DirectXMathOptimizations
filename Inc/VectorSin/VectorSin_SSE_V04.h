#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct VectorSinConstants_SSE_V04
{
	XMVECTOR pi;				// 16 bytes
	XMVECTOR two_pi;			// 16 bytes

	XMVECTOR sign_bit;			// 16 bytes
	XMVECTOR inv_two_pi;		// 16 bytes
	XMVECTOR half_pi;			// 16 bytes

	XMVECTOR coefficients[6];	// 96 bytes

	// Total struct size:		  176 bytes (3 cache lines)
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern VectorSinConstants_SSE_V04 VECTOR_SIN_CONSTANTS_SSE_V04;

// V04 packs all the constants and uses the branchless selection from the reference
inline XMVECTOR XM_CALLCONV XMVectorSin_SSE_V04(FXMVECTOR V)
{
	// 11-degree minimax approximation
	// Force the value within the bounds of pi
	XMVECTOR quotient = _mm_mul_ps(V, VECTOR_SIN_CONSTANTS_SSE_V04.inv_two_pi);
	quotient = _mm_round_ps(quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
	quotient = _mm_mul_ps(quotient, VECTOR_SIN_CONSTANTS_SSE_V04.two_pi);
	XMVECTOR x = _mm_sub_ps(V, quotient);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x).
	XMVECTOR sign = _mm_and_ps(x, VECTOR_SIN_CONSTANTS_SSE_V04.sign_bit);
	XMVECTOR c = _mm_or_ps(VECTOR_SIN_CONSTANTS_SSE_V04.pi, sign);  // pi when x >= 0, -pi when x < 0
	XMVECTOR absx = _mm_andnot_ps(sign, x);  // |x|
	XMVECTOR rflx = _mm_sub_ps(c, x);
	XMVECTOR comp = _mm_cmple_ps(absx, VECTOR_SIN_CONSTANTS_SSE_V04.half_pi);
	XMVECTOR select0 = _mm_and_ps(comp, x);
	XMVECTOR select1 = _mm_andnot_ps(comp, rflx);
	x = _mm_or_ps(select0, select1);

	XMVECTOR x2 = _mm_mul_ps(x, x);

	// Compute polynomial approximation
	XMVECTOR Result = _mm_mul_ps(x2, VECTOR_SIN_CONSTANTS_SSE_V04.coefficients[0]);
	Result = _mm_add_ps(Result, VECTOR_SIN_CONSTANTS_SSE_V04.coefficients[1]);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, VECTOR_SIN_CONSTANTS_SSE_V04.coefficients[2]);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, VECTOR_SIN_CONSTANTS_SSE_V04.coefficients[3]);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, VECTOR_SIN_CONSTANTS_SSE_V04.coefficients[4]);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, VECTOR_SIN_CONSTANTS_SSE_V04.coefficients[5]);
	Result = _mm_mul_ps(Result, x);
	return Result;
}
