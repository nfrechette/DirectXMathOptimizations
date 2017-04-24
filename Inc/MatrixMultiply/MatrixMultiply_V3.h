#pragma once

extern void XM_CALLCONV XMMatrixMultiply_V3_RegExp2_Impl(const float* M1, float* mResult, XMVECTOR M2R0, XMVECTOR M2R1, XMVECTOR M2R2, XMVECTOR M2R3);
extern void XMMatrixMultiply_V3_Mem2_Impl(const float* M1, const float* M2, float* mResult);

#define XMMatrixMultiply_V3_RegExp2(M1, M2, Result) XMMatrixMultiply_V3_RegExp2_Impl(reinterpret_cast<float*>(&M1), reinterpret_cast<float*>(&Result), M2.r[0], M2.r[1], M2.r[2], M2.r[3])
#define XMMatrixMultiply_V3_Mem2(M1, M2, Result) XMMatrixMultiply_V3_Mem2_Impl(reinterpret_cast<float*>(&M1), reinterpret_cast<float*>(&M2), reinterpret_cast<float*>(&Result))
