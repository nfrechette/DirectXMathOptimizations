#pragma once

#include <DirectXMath.h>

using namespace DirectX;

constexpr XMVECTOR SIN_COEFF0_FMA_V00 = { -2.3889859e-08f, -2.3889859e-08f, -2.3889859e-08f, -2.3889859e-08f };
constexpr XMVECTOR SIN_COEFF1_FMA_V00 = { 2.7525562e-06f, 2.7525562e-06f, 2.7525562e-06f, 2.7525562e-06f };
constexpr XMVECTOR SIN_COEFF2_FMA_V00 = { -0.00019840874f, -0.00019840874f, -0.00019840874f, -0.00019840874f };
constexpr XMVECTOR SIN_COEFF3_FMA_V00 = { 0.0083333310f, 0.0083333310f, 0.0083333310f, 0.0083333310f };
constexpr XMVECTOR SIN_COEFF4_FMA_V00 = { -0.16666667f, -0.16666667f, -0.16666667f, -0.16666667f };
constexpr XMVECTOR SIN_COEFF5_FMA_V00 = { 1.0f, 1.0f, 1.0f, 1.0f };

// V00 starts with SSE_V04 without constant packing and adds FMA to it
inline XMVECTOR XM_CALLCONV XMVectorSin_FMA_V00(FXMVECTOR V)
{
	// 11-degree minimax approximation
	// Force the value within the bounds of pi
	XMVECTOR quotient = _mm_mul_ps(V, g_XMReciprocalTwoPi);
	quotient = _mm_round_ps(quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);

	XMVECTOR x = _mm_fnmadd_ps(quotient, g_XMTwoPi, V);

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
	XMVECTOR Result = _mm_fmadd_ps(x2, SIN_COEFF0_FMA_V00, SIN_COEFF1_FMA_V00);
	Result = _mm_fmadd_ps(Result, x2, SIN_COEFF2_FMA_V00);
	Result = _mm_fmadd_ps(Result, x2, SIN_COEFF3_FMA_V00);
	Result = _mm_fmadd_ps(Result, x2, SIN_COEFF4_FMA_V00);
	Result = _mm_fmadd_ps(Result, x2, SIN_COEFF5_FMA_V00);
	Result = _mm_mul_ps(Result, x);
	return Result;
}
