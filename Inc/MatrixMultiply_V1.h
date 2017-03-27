#pragma once

#include <DirectXMath.h>

using namespace DirectX;

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_V1_Reg(FXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2.r[0]);
		vY = _mm_mul_ps(vY, M2.r[1]);
		vZ = _mm_mul_ps(vZ, M2.r[2]);
		vW = _mm_mul_ps(vW, M2.r[3]);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
	return mResult;
}

inline void XM_CALLCONV XMMatrixMultiply_V1_Reg2(FXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2R0);
		vY = _mm_mul_ps(vY, M2R1);
		vZ = _mm_mul_ps(vZ, M2R2);
		vW = _mm_mul_ps(vW, M2R3);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_V1_RegFlip_Impl(FXMMATRIX M2, CXMMATRIX M1)
{
	XMMATRIX mResult;
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2.r[0]);
		vY = _mm_mul_ps(vY, M2.r[1]);
		vZ = _mm_mul_ps(vZ, M2.r[2]);
		vW = _mm_mul_ps(vW, M2.r[3]);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
	return mResult;
}

inline void XM_CALLCONV XMMatrixMultiply_V1_RegFlip2_Impl(FXMMATRIX M2, CXMMATRIX M1, XMMATRIX& mResult)
{
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2.r[0]);
		vY = _mm_mul_ps(vY, M2.r[1]);
		vZ = _mm_mul_ps(vZ, M2.r[2]);
		vW = _mm_mul_ps(vW, M2.r[3]);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_V1_RegExp_Impl(CXMMATRIX M1, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	XMMATRIX mResult;
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2R0);
		vY = _mm_mul_ps(vY, M2R1);
		vZ = _mm_mul_ps(vZ, M2R2);
		vW = _mm_mul_ps(vW, M2R3);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
	return mResult;
}

inline void XM_CALLCONV XMMatrixMultiply_V1_RegExp2_Impl(CXMMATRIX M1, XMMATRIX& mResult, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2R0);
		vY = _mm_mul_ps(vY, M2R1);
		vZ = _mm_mul_ps(vZ, M2R2);
		vW = _mm_mul_ps(vW, M2R3);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
}

inline XMMATRIX XM_CALLCONV XMMatrixMultiply_V1_Mem(CXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2.r[0]);
		vY = _mm_mul_ps(vY, M2.r[1]);
		vZ = _mm_mul_ps(vZ, M2.r[2]);
		vW = _mm_mul_ps(vW, M2.r[3]);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
	return mResult;
}

inline void XM_CALLCONV XMMatrixMultiply_V1_Mem2(CXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2R0);
		vY = _mm_mul_ps(vY, M2R1);
		vZ = _mm_mul_ps(vZ, M2R2);
		vW = _mm_mul_ps(vW, M2R3);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
}

__forceinline XMMATRIX XM_CALLCONV XMMatrixMultiply_V1_Inl(FXMMATRIX M1, CXMMATRIX M2)
{
	XMMATRIX mResult;
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2.r[0]);
		vY = _mm_mul_ps(vY, M2.r[1]);
		vZ = _mm_mul_ps(vZ, M2.r[2]);
		vW = _mm_mul_ps(vW, M2.r[3]);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
	return mResult;
}

__forceinline void XM_CALLCONV XMMatrixMultiply_V1_Inl2(FXMMATRIX M1, CXMMATRIX M2, XMMATRIX& mResult)
{
	const XMVECTOR M2R0 = M2.r[0];
	const XMVECTOR M2R1 = M2.r[1];
	const XMVECTOR M2R2 = M2.r[2];
	const XMVECTOR M2R3 = M2.r[3];

	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2R0);
		vY = _mm_mul_ps(vY, M2R1);
		vZ = _mm_mul_ps(vZ, M2R2);
		vW = _mm_mul_ps(vW, M2R3);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
}

__forceinline XMMATRIX XM_CALLCONV XMMatrixMultiply_V1_InlExp_Impl(CXMMATRIX M1, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	XMMATRIX mResult;
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2R0);
		vY = _mm_mul_ps(vY, M2R1);
		vZ = _mm_mul_ps(vZ, M2R2);
		vW = _mm_mul_ps(vW, M2R3);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
	return mResult;
}

__forceinline void XM_CALLCONV XMMatrixMultiply_V1_InlExp2_Impl(CXMMATRIX M1, XMMATRIX& mResult, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3)
{
	for (int i = 3; i >= 0; --i)
	{
		XMVECTOR vX = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 0);
		XMVECTOR vY = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 1);
		XMVECTOR vZ = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 2);
		XMVECTOR vW = _mm_broadcast_ss(reinterpret_cast<const float*>(&M1.r[i]) + 3);
		// Perform the operation on the first row
		vX = _mm_mul_ps(vX, M2R0);
		vY = _mm_mul_ps(vY, M2R1);
		vZ = _mm_mul_ps(vZ, M2R2);
		vW = _mm_mul_ps(vW, M2R3);
		// Perform a binary add to reduce cumulative errors
		vX = _mm_add_ps(vX, vZ);
		vY = _mm_add_ps(vY, vW);
		vX = _mm_add_ps(vX, vY);
		mResult.r[i] = vX;
	}
}

//////////////////////////////////////////////////////////////////////////

#define XMMatrixMultiply_V1_RegFlip(M1, M2) XMMatrixMultiply_V1_RegFlip_Impl(M2, M1)
#define XMMatrixMultiply_V1_RegFlip2(M1, M2, Result) XMMatrixMultiply_V1_RegFlip2_Impl(M2, M1, Result)
#define XMMatrixMultiply_V1_RegExp(M1, M2) XMMatrixMultiply_V1_RegExp_Impl(M1, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_V1_RegExp2(M1, M2, Result) XMMatrixMultiply_V1_RegExp2_Impl(M1, Result, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_V1_InlExp(M1, M2) XMMatrixMultiply_V1_InlExp_Impl(M1, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_V1_InlExp2(M1, M2, Result) XMMatrixMultiply_V1_InlExp2_Impl(M1, Result, M2.r[0], M2.r[1], M2.r[2], M2.r[3])
