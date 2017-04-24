#pragma once

#include <DirectXMath.h>

using namespace DirectX;

constexpr uint32_t SIGN_BIT_MASK_SSE_V00 = 0x80000000;
constexpr XMVECTOR XM_HALF_SSE_V00 = { 0.5f, 0.5f, 0.5f, 0.5f };
constexpr XMVECTOR XM_PI_SSE_V00 = { XM_PI, XM_PI, XM_PI, XM_PI };
constexpr XMVECTOR XM_2PI_SSE_V00 = { XM_2PI, XM_2PI, XM_2PI, XM_2PI };
constexpr XMVECTOR XM_1DIV2PI_SSE_V00 = { XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI };
constexpr XMVECTOR XM_PIDIV2_SSE_V00 = { XM_PIDIV2, XM_PIDIV2, XM_PIDIV2, XM_PIDIV2 };

// V10 converts everything to SSE scalar math and removes all branching
// We also use the round intrinsic
__declspec(noinline) float XMScalarSin_SSE_V00(const float Value)
{
	const XMVECTOR sign_bit_mask = _mm_broadcast_ss((float*)&SIGN_BIT_MASK_SSE_V00);

	XMVECTOR value_v = _mm_set_ps1(Value);
	XMVECTOR value_sign = _mm_and_ps(value_v, sign_bit_mask);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	XMVECTOR quotient = _mm_mul_ss(value_v, XM_1DIV2PI_SSE_V00);
	// If Value >= 0.0, our rounding offset is 0.5, otherwise -0.5, same sign as Value
	XMVECTOR rounding_offset = _mm_or_ps(value_sign, XM_HALF_SSE_V00);
	quotient = _mm_add_ss(quotient, rounding_offset);
	quotient = _mm_round_ss(quotient, quotient, _MM_FROUND_TO_ZERO);

	XMVECTOR y = _mm_sub_ss(value_v, _mm_mul_ss(quotient, XM_2PI_SSE_V00));
	// 1 and, 1 andnot, 1 cmp, 1 or, 1 sub, 1 blendv, 2 mov = 8 instructions
	// The compiler generates 2 mov instructions here, I'm not sure why, we only need 4 values
	// but the compiler seems to favor not outputting a value in one of the input registers
	XMVECTOR y_sign = _mm_and_ps(y, sign_bit_mask);
	XMVECTOR y_abs = _mm_andnot_ps(sign_bit_mask, y);
	XMVECTOR y_abs_le_halfpi = _mm_cmple_ss(y_abs, XM_PIDIV2_SSE_V00);
	// If |y| > pi/2, offset = y_sign * XM_PI, else offset = 0.0
	XMVECTOR offset = _mm_or_ps(y_sign, XM_PI_SSE_V00);
	// If |y| > pi/2, y = -(y + offset), else y = y
	y = _mm_blendv_ps(_mm_sub_ss(offset, y), y, y_abs_le_halfpi);

	float y_scalar = _mm_cvtss_f32(y);

	// 11-degree minimax approximation
	float y2 = y_scalar * y_scalar;
	return (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y_scalar;
}
