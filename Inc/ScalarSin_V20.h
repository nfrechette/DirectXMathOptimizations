#pragma once

#include <DirectXMath.h>

using namespace DirectX;

constexpr uint32_t SIGN_BIT_MASK_V20 = 0x80000000;
constexpr XMVECTOR XM_HALF_V20 = { 0.5f, 0.5f, 0.5f, 0.5f };
constexpr XMVECTOR XM_PI_V20 = { XM_PI, XM_PI, XM_PI, XM_PI };
constexpr XMVECTOR XM_NEG_PI_V20 = { -XM_PI, -XM_PI, -XM_PI, -XM_PI };
constexpr XMVECTOR XM_2PI_V20 = { XM_2PI, XM_2PI, XM_2PI, XM_2PI };
constexpr XMVECTOR XM_1DIV2PI_V20 = { XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI };
constexpr XMVECTOR XM_PIDIV2_V20 = { XM_PIDIV2, XM_PIDIV2, XM_PIDIV2, XM_PIDIV2 };
constexpr XMVECTOR XM_NEG_PIDIV2_V20 = { -XM_PIDIV2, -XM_PIDIV2, -XM_PIDIV2, -XM_PIDIV2 };

constexpr XMVECTOR SIN_COEFF0_V20 = { -2.3889859e-08f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF1_V20 = { 2.7525562e-06f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF2_V20 = { 0.00019840874f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF3_V20 = { 0.0083333310f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF4_V20 = { 0.16666667f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF5_V20 = { 1.0f, 0, 0, 0 };

// V20 tries to leverage FMA as much as possible
// The first branch is removed, the second kept
__declspec(noinline) float XMScalarSin_V20(const float Value)
{
	const XMVECTOR value_v = _mm_set_ps1(Value);

	XMVECTOR quotient = _mm_mul_ss(value_v, XM_1DIV2PI_V20);
	quotient = _mm_round_ss(quotient, quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);

	XMVECTOR y = _mm_fnmadd_ss(quotient, XM_2PI_V20, value_v);
	if (_mm_comigt_ss(y, XM_PIDIV2_V20))
	{
		y = _mm_sub_ss(XM_PI_V20, y);	// 1 cmp, 1 sub, 3 mov, 2 jmp = 7 instructions
	}
	else if (!_mm_comilt_ss(XM_NEG_PIDIV2_V20, y))
	{
		y = _mm_sub_ss(XM_NEG_PI_V20, y);	// 2 cmp, 1 sub, 3 mov, 2 jmp = 8 instructions
	}
	else
	{
		// 2 cmp, 2 jmp, 1 mov = 5 instructions
	}

	// 11-degree minimax approximation
	XMVECTOR y2 = _mm_mul_ss(y, y);
	XMVECTOR result = _mm_fmadd_ss(y2, SIN_COEFF0_V20, SIN_COEFF1_V20);
	result = _mm_fmsub_ss(result, y2, SIN_COEFF2_V20);
	result = _mm_fmadd_ss(result, y2, SIN_COEFF3_V20);
	result = _mm_fmsub_ss(result, y2, SIN_COEFF4_V20);
	result = _mm_fmadd_ss(result, y2, SIN_COEFF5_V20);
	result = _mm_mul_ss(result, y);
	return _mm_cvtss_f32(result);
}
