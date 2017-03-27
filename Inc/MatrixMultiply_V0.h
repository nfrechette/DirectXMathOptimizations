#pragma once

#include <DirectXMath.h>

using namespace DirectX;

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_V0_Reg(FXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
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

inline void XM_CALLCONV XMMatrixMultiply_V0_Reg2(FXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_V0_RegFlip_Impl(FXMMATRIX M2, CXMMATRIX M1)
{
	XMMATRIX mResult;
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
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

inline void XM_CALLCONV XMMatrixMultiply_V0_RegFlip2_Impl(FXMMATRIX M2, CXMMATRIX M1, XMMATRIX& mResult)
{
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_V0_RegExp_Impl(CXMMATRIX M1, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	XMMATRIX mResult;
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
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

inline void XM_CALLCONV XMMatrixMultiply_V0_RegExp2_Impl(CXMMATRIX M1, XMMATRIX& mResult, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_V0_Mem(CXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
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

inline void XM_CALLCONV XMMatrixMultiply_V0_Mem2(CXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

__forceinline XMMATRIX XM_CALLCONV XMMatrixMultiply_V0_Inl(FXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2.r[0]);
	vY = _mm_mul_ps(vY, M2.r[1]);
	vZ = _mm_mul_ps(vZ, M2.r[2]);
	vW = _mm_mul_ps(vW, M2.r[3]);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
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

__forceinline void XM_CALLCONV XMMatrixMultiply_V0_Inl2(FXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[3] = vX;
}

__forceinline XMMATRIX XM_CALLCONV XMMatrixMultiply_V0_InlExp_Impl(CXMMATRIX M1, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	XMMATRIX mResult;
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
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

__forceinline void XM_CALLCONV XMMatrixMultiply_V0_InlExp2_Impl(CXMMATRIX M1, XMMATRIX& mResult, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	// Splat the component X,Y,Z then W
	XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 0);
	XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 1);
	XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 2);
	XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[0]) + 3);
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
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[1]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[1] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[2]) + 3);
	vX = _mm_mul_ps(vX, M2R0);
	vY = _mm_mul_ps(vY, M2R1);
	vZ = _mm_mul_ps(vZ, M2R2);
	vW = _mm_mul_ps(vW, M2R3);
	vX = _mm_add_ps(vX, vZ);
	vY = _mm_add_ps(vY, vW);
	vX = _mm_add_ps(vX, vY);
	mResult.r[2] = vX;
	vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 0);
	vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 1);
	vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 2);
	vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[3]) + 3);
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

#define XMMatrixMultiply_V0_RegFlip(M1, M2) XMMatrixMultiply_V0_RegFlip_Impl(M2, M1)
#define XMMatrixMultiply_V0_RegFlip2(M1, M2, Result) XMMatrixMultiply_V0_RegFlip2_Impl(M2, M1, Result)
#define XMMatrixMultiply_V0_RegExp(M1, M2) XMMatrixMultiply_V0_RegExp_Impl(M1,M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_V0_RegExp2(M1, M2, Result) XMMatrixMultiply_V0_RegExp2_Impl(M1, Result, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_V0_InlExp(M1, M2) XMMatrixMultiply_V0_InlExp_Impl(M1, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_V0_InlExp2(M1, M2, Result) XMMatrixMultiply_V0_InlExp2_Impl(M1, Result, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
