#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// V00 performs bankers rounding inline, for clarity
inline XMVECTOR XM_CALLCONV XMVectorSin_SSE_V00(FXMVECTOR V)
{
	// 11-degree minimax approximation
	// Force the value within the bounds of pi
	XMVECTOR quotient = _mm_mul_ps(V, g_XMReciprocalTwoPi);
	quotient = _mm_round_ps(quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
	quotient = _mm_mul_ps(quotient, g_XMTwoPi);
	XMVECTOR x = _mm_sub_ps(V, quotient);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x).
	XMVECTOR sign = _mm_and_ps(x, g_XMNegativeZero);
	XMVECTOR c = _mm_or_ps(g_XMPi, sign);  // pi when x >= 0, -pi when x < 0
	XMVECTOR absx = _mm_andnot_ps(sign, x);  // |x|
	XMVECTOR rflx = _mm_sub_ps(c, x);
	XMVECTOR comp = _mm_cmple_ps(absx, g_XMHalfPi);
	XMVECTOR select0 = _mm_and_ps(comp, x);
	XMVECTOR select1 = _mm_andnot_ps(comp, rflx);
	x = _mm_or_ps(select0, select1);

	XMVECTOR x2 = _mm_mul_ps(x, x);

	// Compute polynomial approximation
	const XMVECTOR SC1 = g_XMSinCoefficients1;
	XMVECTOR vConstants = XM_PERMUTE_PS(SC1, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR Result = _mm_mul_ps(vConstants, x2);

	const XMVECTOR SC0 = g_XMSinCoefficients0;
	vConstants = XM_PERMUTE_PS(SC0, _MM_SHUFFLE(3, 3, 3, 3));
	Result = _mm_add_ps(Result, vConstants);
	Result = _mm_mul_ps(Result, x2);

	vConstants = XM_PERMUTE_PS(SC0, _MM_SHUFFLE(2, 2, 2, 2));
	Result = _mm_add_ps(Result, vConstants);
	Result = _mm_mul_ps(Result, x2);

	vConstants = XM_PERMUTE_PS(SC0, _MM_SHUFFLE(1, 1, 1, 1));
	Result = _mm_add_ps(Result, vConstants);
	Result = _mm_mul_ps(Result, x2);

	vConstants = XM_PERMUTE_PS(SC0, _MM_SHUFFLE(0, 0, 0, 0));
	Result = _mm_add_ps(Result, vConstants);
	Result = _mm_mul_ps(Result, x2);
	Result = _mm_add_ps(Result, g_XMOne);
	Result = _mm_mul_ps(Result, x);
	return Result;
}
