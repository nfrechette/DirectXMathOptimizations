#pragma once

#include <DirectXMath.h>

using namespace DirectX;

constexpr float HALF_SSE_V09 = 0.5f;
constexpr float NEG_HALF_SSE_V09 = -0.5f;
constexpr XMVECTOR XM_HALF_SSE_V09 = { 0.5f, 0.5f, 0.5f, 0.5f };
constexpr XMVECTOR XM_PI_SSE_V09 = { XM_PI, XM_PI, XM_PI, XM_PI };
constexpr XMVECTOR XM_NEG_PI_SSE_V09 = { -XM_PI, -XM_PI, -XM_PI, -XM_PI };
constexpr XMVECTOR XM_2PI_SSE_V09 = { XM_2PI, XM_2PI, XM_2PI, XM_2PI };
constexpr XMVECTOR XM_1DIV2PI_SSE_V09 = { XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI, XM_1DIV2PI };
constexpr XMVECTOR XM_PIDIV2_SSE_V09 = { XM_PIDIV2, XM_PIDIV2, XM_PIDIV2, XM_PIDIV2 };
constexpr XMVECTOR XM_NEG_PIDIV2_SSE_V09 = { -XM_PIDIV2, -XM_PIDIV2, -XM_PIDIV2, -XM_PIDIV2 };

// V09 is based on 08 but uses banker's rounding
// The ScalarSin reference implementation uses symmetric rounding but VectorSin uses banker's rounding
// Symmetric rounding behaves like this:
//    [ 0.0 ...  0.5[  ->   0.0
//    [ 0.5 ...  1.5[  ->   1.0
//    [ 1.5 ...  2.5[  ->   2.0
//    ]-0.5 ...  0.0]  ->   0.0
//    ]-1.5 ... -0.5]  ->  -1.0
//    ]-2.5 ... -1.5]  ->  -2.0
//
// Banker's rounding behaves like this:
//    [ 0.0 ...  0.5]  ->   0.0
//    ] 0.5 ...  1.5[  ->   1.0
//    [ 1.5 ...  2.5]  ->   2.0
//    [-0.5 ...  0.0]  ->   0.0
//    ]-1.5 ... -0.5[  ->  -1.0
//    [-2.5 ... -1.5]  ->  -2.0
//
// For our purposes, they are both equivalent because the rounded value only differs at the mid point x.5
// In our case, since we divide the input by 2*PI, the mid point is PI, 3 * PI, 5 * PI, -PI, -3 * PI, -5 * PI
// The behavior only differs when we would end up rounding to PI, banker's rounding will occasionally flip the sign to -PI
// Fortunately, sin(PI) == sin(-PI)
// Here is how it behaves:
//    0.0    / (2 * PI) -> round( 0.00)  ->  0.0    - (0.0 * 2 * PI)  ->  0.0
//    (PI/2) / (2 * PI) -> round( 0.25)  ->  (PI/2) - (0.0 * 2 * PI)  ->  PI/2
//    PI     / (2 * PI) -> round( 0.50)  ->  PI     - (0.0 * 2 * PI)  ->  PI      (with symmetric: PI     - ( 1.0 * 2 * PI)  -> -PI)
//    (2*PI) / (2 * PI) -> round( 1.00)  ->  (2*PI) - (1.0 * 2 * PI)  ->  0.0
//    (3*PI) / (2 * PI) -> round( 1.50)  ->  (3*PI) - (2.0 * 2 * PI)  -> -PI
//    (5*PI) / (2 * PI) -> round( 2.50)  ->  (5*PI) - (2.0 * 2 * PI)  ->  PI      (with symmetric: (5*PI) - ( 3.0 * 2 * PI)  -> -PI)
//   -PI     / (2 * PI) -> round(-0.50)  -> -PI     - (0.0 * 2 * PI)  -> -PI      (with symmetric: -PI    - (-1.0 * 2 * PI)  ->  PI)
__declspec(noinline) float XMScalarSin_SSE_V09(const float Value)
{
	const XMVECTOR value_v = _mm_set_ps1(Value);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	XMVECTOR quotient = _mm_mul_ss(value_v, XM_1DIV2PI_SSE_V09);
	quotient = _mm_round_ss(quotient, quotient, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);

	XMVECTOR y = _mm_sub_ss(value_v, _mm_mul_ss(quotient, XM_2PI_SSE_V09));
	if (_mm_comigt_ss(y, XM_PIDIV2_SSE_V09))
	{
		y = _mm_sub_ss(XM_PI_SSE_V09, y);	// 1 cmp, 1 sub, 3 mov, 2 jmp = 7 instructions
	}
	else if (!_mm_comile_ss(XM_NEG_PIDIV2_SSE_V09, y))
	{
		y = _mm_sub_ss(XM_NEG_PI_SSE_V09, y);	// 2 cmp, 1 sub, 3 mov, 2 jmp = 8 instructions
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
