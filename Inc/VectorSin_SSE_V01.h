#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// V01 performs the branchless selection differently
inline XMVECTOR XM_CALLCONV XMVectorSin_SSE_V01(FXMVECTOR V)
{
	// 11-degree minimax approximation
	// Force the value within the bounds of pi
	XMVECTOR quotient = _mm_mul_ps(V, g_XMReciprocalTwoPi);
	quotient = _mm_round_ps(quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
	quotient = _mm_mul_ps(quotient, g_XMTwoPi);
	XMVECTOR x = _mm_sub_ps(V, quotient);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x).
	XMVECTOR x_sign = _mm_and_ps(x, g_XMNegativeZero);
	XMVECTOR x_abs = _mm_andnot_ps(g_XMNegativeZero, x);
	XMVECTOR x_abs_le_halfpi = _mm_cmple_ps(x_abs, g_XMHalfPi);
	// If |y| > pi/2, offset = y_sign * XM_PI, else offset = 0.0
	XMVECTOR offset = _mm_or_ps(x_sign, g_XMPi);
	// If |y| > pi/2, y = -(y + offset), else y = y
	x = _mm_blendv_ps(_mm_sub_ps(offset, x), x, x_abs_le_halfpi);

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
