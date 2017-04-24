#pragma once

#include <DirectXMath.h>

using namespace DirectX;

// This is the original DirectXMath implementation, as is, for SSE only
inline XMMATRIX XM_CALLCONV XMMatrixMultiply_Ref_Reg(FXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
	return mResult;
}

inline void XM_CALLCONV XMMatrixMultiply_Ref_Reg2(FXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_Ref_RegFlip_Impl(FXMMATRIX M2, CXMMATRIX M1)
{
	XMMATRIX mResult;
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
	return mResult;
}

inline void XM_CALLCONV XMMatrixMultiply_Ref_RegFlip2_Impl(FXMMATRIX M2, CXMMATRIX M1, XMMATRIX& mResult)
{
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_Ref_RegExp_Impl(CXMMATRIX M1, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	XMMATRIX mResult;
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
	return mResult;
}

inline void XM_CALLCONV XMMatrixMultiply_Ref_RegExp2_Impl(CXMMATRIX M1, XMMATRIX& mResult, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_Ref_Mem(CXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
	return mResult;
}

inline void XM_CALLCONV XMMatrixMultiply_Ref_Mem2(CXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

__forceinline XMMATRIX XM_CALLCONV XMMatrixMultiply_Ref_Inl(FXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
	return mResult;
}

__forceinline void XM_CALLCONV XMMatrixMultiply_Ref_Inl2(FXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

__forceinline XMMATRIX XM_CALLCONV XMMatrixMultiply_Ref_InlExp_Impl(CXMMATRIX M1, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	XMMATRIX mResult;
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
	return mResult;
}

__forceinline void XM_CALLCONV XMMatrixMultiply_Ref_InlExp2_Impl(CXMMATRIX M1, XMMATRIX& mResult, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	// Use vW to hold the original row
	XMVECTOR vW = M1.r[0];
	// Splat the component X,Y,Z then W
	XMVECTOR vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	XMVECTOR vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	XMVECTOR vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	// Perform the operation on the first row
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	// Perform a binary add to reduce cumulative errors
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[0] = vX;
	// Repeat for the other 3 rows
	vW = M1.r[1];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vW = M1.r[2];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vW = M1.r[3];
	vX = XM_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
	vY = XM_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
	vZ = XM_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
	vW = XM_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

//////////////////////////////////////////////////////////////////////////

#define XMMatrixMultiply_Ref_RegFlip(M1, M2) XMMatrixMultiply_Ref_RegFlip_Impl(M2, M1)
#define XMMatrixMultiply_Ref_RegFlip2(M1, M2, Result) XMMatrixMultiply_Ref_RegFlip2_Impl(M2, M1, Result)
#define XMMatrixMultiply_Ref_RegExp(M1, M2) XMMatrixMultiply_Ref_RegExp_Impl(M1, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_Ref_RegExp2(M1, M2, Result) XMMatrixMultiply_Ref_RegExp2_Impl(M1, Result, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_Ref_InlExp(M1, M2) XMMatrixMultiply_Ref_InlExp_Impl(M1, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_Ref_InlExp2(M1, M2, Result) XMMatrixMultiply_Ref_InlExp2_Impl(M1, Result, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
