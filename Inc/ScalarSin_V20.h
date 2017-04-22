#pragma once

#include <DirectXMath.h>

using namespace DirectX;

constexpr uint32_t SIGN_BIT_MASK_V20 = 0x80000000;
constexpr XMVECTOR XM_HALF_V20 = { 0.5f, 0.5f, 0.5f, 0.5f };
constexpr XMVECTOR XM_PI_V20 = { XM_PI, XM_PI, XM_PI, XM_PI };
constexpr XMVECTOR XM_2PI_V20 = { XM_2PI, XM_2PI, XM_2PI, XM_2PI };
constexpr XMVECTOR XM_1DIV2PI_V20 = { XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI };
constexpr XMVECTOR XM_PIDIV2_V20 = { XM_PIDIV2, XM_PIDIV2, XM_PIDIV2, XM_PIDIV2 };

constexpr XMVECTOR SIN_COEFF0_V20 = { -2.3889859e-08f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF1_V20 = { 2.7525562e-06f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF2_V20 = { 0.00019840874f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF3_V20 = { 0.0083333310f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF4_V20 = { 0.16666667f, 0, 0, 0 };
constexpr XMVECTOR SIN_COEFF5_V20 = { 1.0f, 0, 0, 0 };

__declspec(noinline) float XMScalarSin_V20(const float Value)
{
	const XMVECTOR value_v = _mm_set_ps1(Value);
	const XMVECTOR value_sign = _mm_and_ps(value_v, *(XMVECTOR*)&SIGN_BIT_MASK_V20);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	// If Value >= 0.0, our rounding offset is 0.5, otherwise -0.5, same sign as Value
	const XMVECTOR rounding_offset = _mm_or_ps(value_sign, XM_HALF_V20);
	XMVECTOR quotient = _mm_fmadd_ss(value_v, XM_1DIV2PI_V20, rounding_offset);
	//XMVECTOR quotient = _mm_add_ss(_mm_mul_ss(value_v, XM_1DIV2PI_V10), rounding_offset);
	quotient = _mm_cvt_si2ss(quotient, _mm_cvtt_ss2si(quotient));

	XMVECTOR y = _mm_fnmadd_ss(quotient, XM_2PI_V20, value_v);
	//XMVECTOR y = _mm_sub_ss(value_v, _mm_mul_ss(quotient, XM_2PI_V10));
	if (_mm_comigt_ss(y, XM_PIDIV2_V20))
	{
		y = _mm_sub_ss(XM_PI_V20, y);
	}
	else if (_mm_comilt_ss(y, -XM_PIDIV2_V20))
	{
		y = _mm_sub_ss(-XM_PI_V20, y);
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
