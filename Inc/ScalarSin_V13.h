#pragma once

#include <DirectXMath.h>

using namespace DirectX;

constexpr uint32_t SIGN_BIT_MASK_V13 = 0x80000000;
constexpr XMVECTOR XM_HALF_V13 = { 0.5f, 0.5f, 0.5f, 0.5f };
constexpr XMVECTOR XM_PI_V13 = { XM_PI, XM_PI, XM_PI, XM_PI };
constexpr XMVECTOR XM_2PI_V13 = { XM_2PI, XM_2PI, XM_2PI, XM_2PI };
constexpr XMVECTOR XM_1DIV2PI_V13 = { XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI };
constexpr XMVECTOR XM_PIDIV2_V13 = { XM_PIDIV2, XM_PIDIV2, XM_PIDIV2, XM_PIDIV2 };

// V12 brings back the second branch but compares only once with the absolute value
__declspec(noinline) float XMScalarSin_V13(const float Value)
{
	const XMVECTOR value_v = _mm_set_ps1(Value);
	const XMVECTOR sign_bit_mask = _mm_broadcast_ss((float*)&SIGN_BIT_MASK_V13);
	const XMVECTOR value_sign = _mm_and_ps(value_v, sign_bit_mask);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	XMVECTOR quotient = _mm_mul_ss(value_v, XM_1DIV2PI_V13);
	// If Value >= 0.0, our rounding offset is 0.5, otherwise -0.5, same sign as Value
	const XMVECTOR rounding_offset = _mm_or_ps(value_sign, XM_HALF_V13);
	quotient = _mm_add_ss(quotient, rounding_offset);
	quotient = _mm_round_ss(quotient, quotient, _MM_FROUND_TO_ZERO);

	XMVECTOR y = _mm_sub_ss(value_v, _mm_mul_ss(quotient, XM_2PI_V13));
	const XMVECTOR y_abs = _mm_andnot_ps(sign_bit_mask, y);
	if (_mm_comigt_ss(y_abs, XM_PIDIV2_V13))
	{
		const XMVECTOR y_sign = _mm_and_ps(y, sign_bit_mask);
		const XMVECTOR offset = _mm_or_ps(y_sign, XM_PI_V13);
		y = _mm_sub_ss(offset, y);
		// 1 cmp, 1 andnot, 1 and, 1 or, 1 sub, 1 jmp = 6 instructions
	}
	else
	{
		// 1 cmp, 1 andnot, 1 jmp = 3 instructions
	}

	float y_scalar = _mm_cvtss_f32(y);

	// 11-degree minimax approximation
	float y2 = y_scalar * y_scalar;
	return (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y_scalar;
}
