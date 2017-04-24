#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// This is the original DirectXMath implementation, as is, for SSE only
inline XMVECTOR XM_CALLCONV XMVectorRound_Ref(FXMVECTOR V)
{
#if defined(_XM_SSE4_INTRINSICS_)
	return _mm_round_ps(V, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 sign = _mm_and_ps(V, g_XMNegativeZero);
	__m128 sMagic = _mm_or_ps(g_XMNoFraction, sign);
	__m128 R1 = _mm_add_ps(V, sMagic);
	R1 = _mm_sub_ps(R1, sMagic);
	__m128 R2 = _mm_and_ps(V, g_XMAbsMask);
	__m128 mask = _mm_cmple_ps(R2, g_XMNoFraction);
	R2 = _mm_andnot_ps(mask, V);
	R1 = _mm_and_ps(R1, mask);
	XMVECTOR vResult = _mm_xor_ps(R1, R2);
	return vResult;
#endif
}

// This is the original DirectXMath implementation, as is, for SSE only
inline XMVECTOR XM_CALLCONV XMVectorModAngles_Ref(FXMVECTOR Angles)
{
	// Modulo the range of the given angles such that -XM_PI <= Angles < XM_PI
	XMVECTOR vResult = _mm_mul_ps(Angles, g_XMReciprocalTwoPi);
	// Use the inline function due to complexity for rounding
	vResult = XMVectorRound_Ref(vResult);
	vResult = _mm_mul_ps(vResult, g_XMTwoPi);
	vResult = _mm_sub_ps(Angles, vResult);
	return vResult;
}

// This is the original DirectXMath implementation, as is, for SSE only
inline XMVECTOR XM_CALLCONV XMVectorSin_Ref(FXMVECTOR V)
{
	// 11-degree minimax approximation
	// Force the value within the bounds of pi
	XMVECTOR x = XMVectorModAngles_Ref(V);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x).
	__m128 sign = _mm_and_ps(x, g_XMNegativeZero);
	__m128 c = _mm_or_ps(g_XMPi, sign);  // pi when x >= 0, -pi when x < 0
	__m128 absx = _mm_andnot_ps(sign, x);  // |x|
	__m128 rflx = _mm_sub_ps(c, x);
	__m128 comp = _mm_cmple_ps(absx, g_XMHalfPi);
	__m128 select0 = _mm_and_ps(comp, x);
	__m128 select1 = _mm_andnot_ps(comp, rflx);
	x = _mm_or_ps(select0, select1);

	__m128 x2 = _mm_mul_ps(x, x);

	// Compute polynomial approximation
	const XMVECTOR SC1 = g_XMSinCoefficients1;
	XMVECTOR vConstants = XM_PERMUTE_PS(SC1, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Result = _mm_mul_ps(vConstants, x2);

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
