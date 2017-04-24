#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct VectorSinConstants_SSE_V08
{
	// Packed in the order they are used, sorta
	XMVECTOR inv_two_pi;		// 16 bytes
	XMVECTOR coefficients0;		// 16 bytes		(sign bit, pi, coeff0, coeff1)
	XMVECTOR coefficients1;		// 16 bytes		(coeff2, coeff3, coeff4, coeff5)

	float two_pi;				//  4 bytes
	float half_pi;				//  4 bytes

	// Total struct size:		   56 bytes (1 cache lines)
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern VectorSinConstants_SSE_V08 VECTOR_SIN_CONSTANTS_SSE_V08;

// V08 packs 2 other constants and uses load/shuffle instead of broadcast
// Fails to inline
// Uses 8 XMM registers, 47 instructions
inline XMVECTOR XM_CALLCONV XMVectorSin_SSE_V08(FXMVECTOR V)
{
	// 11-degree minimax approximation
	// Force the value within the bounds of pi
	XMVECTOR quotient = _mm_mul_ps(V, VECTOR_SIN_CONSTANTS_SSE_V08.inv_two_pi);
	quotient = _mm_round_ps(quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
	quotient = _mm_mul_ps(quotient, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V08.two_pi));
	XMVECTOR x = _mm_sub_ps(V, quotient);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x).
	const XMVECTOR coefficients0 = VECTOR_SIN_CONSTANTS_SSE_V08.coefficients0;
	XMVECTOR sign = _mm_and_ps(x, XM_PERMUTE_PS(coefficients0, _MM_SHUFFLE(0, 0, 0, 0)));
	XMVECTOR c = _mm_or_ps(XM_PERMUTE_PS(coefficients0, _MM_SHUFFLE(1, 1, 1, 1)), sign);  // pi when x >= 0, -pi when x < 0
	XMVECTOR absx = _mm_andnot_ps(sign, x);  // |x|
	XMVECTOR rflx = _mm_sub_ps(c, x);
	XMVECTOR comp = _mm_cmple_ps(absx, _mm_broadcast_ss(&VECTOR_SIN_CONSTANTS_SSE_V08.half_pi));
	XMVECTOR select0 = _mm_and_ps(comp, x);
	XMVECTOR select1 = _mm_andnot_ps(comp, rflx);
	x = _mm_or_ps(select0, select1);

	XMVECTOR x2 = _mm_mul_ps(x, x);

	// Compute polynomial approximation
	const XMVECTOR coefficients1 = VECTOR_SIN_CONSTANTS_SSE_V08.coefficients1;
	XMVECTOR Result = _mm_mul_ps(x2, XM_PERMUTE_PS(coefficients0, _MM_SHUFFLE(2, 2, 2, 2)));
	Result = _mm_add_ps(Result, XM_PERMUTE_PS(coefficients0, _MM_SHUFFLE(3, 3, 3, 3)));
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, XM_PERMUTE_PS(coefficients1, _MM_SHUFFLE(0, 0, 0, 0)));
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, XM_PERMUTE_PS(coefficients1, _MM_SHUFFLE(1, 1, 1, 1)));
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, XM_PERMUTE_PS(coefficients1, _MM_SHUFFLE(2, 2, 2, 2)));
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, XM_PERMUTE_PS(coefficients1, _MM_SHUFFLE(3, 3, 3, 3)));
	Result = _mm_mul_ps(Result, x);
	return Result;
}
