#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// Align to a cache line
__declspec(align(64)) struct ScalarSinConstants_V24
{
	union
	{
		XMVECTOR packed0;		// 16 bytes

		struct
		{
			float half;			//  4 bytes
			float pi;			//  4 bytes
			float neg_pi;		//  4 bytes
			float two_pi;		//  4 bytes
		};
	};

	uint32_t sign_bit;			//  4 bytes
	float inv_two_pi;			//  4 bytes
	float half_pi;				//  4 bytes
	float neg_half_pi;			//  4 bytes

	float coefficients[6];		// 24 bytes

	// Total struct size:		   56 bytes
};

// Extern instead of constexpr since it forces the compiler to use the cache line
// aligned constants
extern ScalarSinConstants_V24 SCALAR_SIN_CONSTANTS_V24;

// V24 packs all the constants and inlines the function
// Sadly it fails to inline
// It uses: 5 XMM registers, 31 instructions
inline float XMScalarSin_V24(const float Value)
{
	const XMVECTOR value_v = _mm_set_ps1(Value);
	const XMVECTOR sign_bit_mask = _mm_broadcast_ss((float*)&SCALAR_SIN_CONSTANTS_V24.sign_bit);
	const XMVECTOR value_sign = _mm_and_ps(value_v, sign_bit_mask);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	// If Value >= 0.0, our rounding offset is 0.5, otherwise -0.5, same sign as Value
	const XMVECTOR rounding_offset = _mm_or_ps(value_sign, SCALAR_SIN_CONSTANTS_V24.packed0);	// Only rounding_offset.x is valid
	XMVECTOR quotient = _mm_fmadd_ss(value_v, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.inv_two_pi, rounding_offset);

	quotient = _mm_round_ss(quotient, quotient, _MM_FROUND_TO_ZERO);

	XMVECTOR y = _mm_fnmadd_ss(quotient, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.two_pi, value_v);
	if (_mm_comigt_ss(y, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.half_pi))
	{
		y = _mm_sub_ss(*(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.pi, y);	// 1 cmp, 1 sub, 3 mov, 2 jmp = 7 instructions
	}
	else if (!_mm_comilt_ss(*(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.neg_half_pi, y))
	{
		y = _mm_sub_ss(*(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.neg_pi, y);	// 2 cmp, 1 sub, 3 mov, 2 jmp = 8 instructions
	}
	else
	{
		// 2 cmp, 2 jmp, 1 mov = 5 instructions
	}

	// 11-degree minimax approximation
	XMVECTOR y2 = _mm_mul_ss(y, y);
	XMVECTOR result = _mm_fmadd_ss(y2, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.coefficients[0], *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.coefficients[1]);
	result = _mm_fmsub_ss(result, y2, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.coefficients[2]);
	result = _mm_fmadd_ss(result, y2, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.coefficients[3]);
	result = _mm_fmsub_ss(result, y2, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.coefficients[4]);
	result = _mm_fmadd_ss(result, y2, *(XMVECTOR*)&SCALAR_SIN_CONSTANTS_V24.coefficients[5]);
	result = _mm_mul_ss(result, y);
	return _mm_cvtss_f32(result);
}
