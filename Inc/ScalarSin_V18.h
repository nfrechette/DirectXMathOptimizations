#pragma once

#include <DirectXMath.h>

using namespace DirectX;

constexpr uint32_t SIGN_BIT_MASK_V18 = 0x80000000;
constexpr XMVECTOR XM_HALF_V18 = { 0.5f, 0.5f, 0.5f, 0.5f };
constexpr XMVECTOR XM_PI_V18 = { XM_PI, XM_PI, XM_PI, XM_PI };
constexpr XMVECTOR XM_NEG_PI_V18 = { -XM_PI, -XM_PI, -XM_PI, -XM_PI };
constexpr XMVECTOR XM_2PI_V18 = { XM_2PI, XM_2PI, XM_2PI, XM_2PI };
constexpr XMVECTOR XM_1DIV2PI_V18 = { XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI };
constexpr XMVECTOR XM_PIDIV2_V18 = { XM_PIDIV2, XM_PIDIV2, XM_PIDIV2, XM_PIDIV2 };
constexpr XMVECTOR XM_NEG_PIDIV2_V18 = { -XM_PIDIV2, -XM_PIDIV2, -XM_PIDIV2, -XM_PIDIV2 };

// V18 does the first branch the same way that the C++ scalar version ends up with
__declspec(noinline) float XMScalarSin_V18(const float Value)
{
	const XMVECTOR value_v = _mm_set_ps1(Value);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	XMVECTOR quotient = _mm_mul_ss(value_v, XM_1DIV2PI_V18);
	if (Value >= 0.0f)
	{
		quotient = _mm_add_ss(quotient, XM_HALF_V18);
		// 1 mul, 1 cmp, 2 jmp, 1 add = 5 instructions
	}
	else
	{
		quotient = _mm_sub_ss(quotient, XM_HALF_V18);
		// 1 mul, 1 cmp, 1 jmp, 1 sub = 4 instructions
	}

	quotient = _mm_round_ss(quotient, quotient, _MM_FROUND_TO_ZERO);

	XMVECTOR y = _mm_sub_ss(value_v, _mm_mul_ss(quotient, XM_2PI_V18));
	if (_mm_comigt_ss(y, XM_PIDIV2_V18))
	{
		y = _mm_sub_ss(XM_PI_V18, y);	// 1 cmp, 1 sub, 3 mov, 2 jmp = 7 instructions
	}
	else if (!_mm_comilt_ss(XM_NEG_PIDIV2_V18, y))
	{
		y = _mm_sub_ss(XM_NEG_PI_V18, y);	// 2 cmp, 1 sub, 3 mov, 2 jmp = 8 instructions
	}
	else
	{
		// 2 cmp, 2 jmp, 1 mov = 5 instructions
	}

	float y_scalar = _mm_cvtss_f32(y);

	// 11-degree minimax approximation
	float y2 = y_scalar * y_scalar;
	float result = y2 * -2.3889859e-08f;
	result += 2.7525562e-06f;
	result *= y2;
	result -= 0.00019840874f;
	result *= y2;
	result += 0.0083333310f;
	result *= y2;
	result -= 0.16666667f;
	result *= y2;
	result += 1.0f;
	return result * y_scalar;
}