
PUBLIC ?XMMatrixMultiply_V3_Mem2_Impl@@YAXPEBM0PEAM@Z
PUBLIC ?XMMatrixMultiply_V3_RegExp2_Impl@@YQXPEBMPEAMT__m128@@222@Z

; M1 = rcx
; M2 = rdx
; Result = r8
_XMMatrixMultiply_V3_Mem2_Impl SEGMENT ALIGN(32) 'CODE'
?XMMatrixMultiply_V3_Mem2_Impl@@YAXPEBM0PEAM@Z PROC
	vmovups xmm1, xmmword ptr 16[rdx]
	vmovups xmm2, xmmword ptr 32[rdx]
	vmovups xmm3, xmmword ptr 48[rdx]
	mov r9, 48

_loop:
	vmovss xmm4, dword ptr 0[rcx+r9]
	vshufps xmm4, xmm4, xmm4, 0
	vmulps xmm5, xmm4, xmmword ptr [rdx]	; xmm5 = M1.r[_].x * M2.r[0]
	vmovss xmm4, dword ptr 4[rcx+r9]
	vshufps xmm4, xmm4, xmm4, 0
	vmulps xmm0, xmm4, xmm1					; xmm0 = M1.r[_].y * M2.r[1]
	vmovss xmm4, dword ptr 8[rcx+r9]
	vshufps xmm4, xmm4, xmm4, 0
	vmulps xmm4, xmm4, xmm2					; xmm4 = M1.r[_].z * M2.r[2]
	vaddps xmm5, xmm5, xmm4					; xmm5 = (M1.r[_].x * M2.r[0]) + (M1.r[_].z * M2.r[2])
	vmovss xmm4, dword ptr 12[rcx+r9]
	vshufps xmm4, xmm4, xmm4, 0
	vmulps xmm4, xmm4, xmm3					; xmm4 = M1.r[_].w * M2.r[3]
	vaddps xmm0, xmm0, xmm4					; xmm0 = (M1.r[_].y * M2.r[1]) + (M1.r[_].w * M2.r[3])
	vaddps xmm5, xmm5, xmm0
	vmovups xmmword ptr [r8+r9], xmm5
	sub r9, 16
	jge _loop
	ret
?XMMatrixMultiply_V3_Mem2_Impl@@YAXPEBM0PEAM@Z ENDP
_XMMatrixMultiply_V3_Mem2_Impl ENDS

; M1 = rcx
; Result = rdx
; xmm2 = M2.r[0]
; xmm3 = M2.r[1]
; xmm4 = M2.r[2]
; xmm5 = M2.r[3]
_XMMatrixMultiply_V3_RegExp2_Impl SEGMENT ALIGN(32) 'CODE'
?XMMatrixMultiply_V3_RegExp2_Impl@@YQXPEBMPEAMT__m128@@222@Z PROC
	; Write xmm2 to Result.r[0] since it will be written last
	vmovups xmmword ptr [rdx], xmm2
	mov r8, 48

_loop:
	vmovss xmm0, dword ptr 0[rcx+r8]
	vshufps xmm0, xmm0, xmm0, 0
	vmulps xmm1, xmm0, xmmword ptr [rdx]	; xmm1 = M1.r[_].x * M2.r[0]
	vmovss xmm0, dword ptr 4[rcx+r8]
	vshufps xmm0, xmm0, xmm0, 0
	vmulps xmm2, xmm0, xmm3					; xmm2 = M1.r[_].y * M2.r[0]
	vmovss xmm0, dword ptr 8[rcx+r8]
	vshufps xmm0, xmm0, xmm0, 0
	vmulps xmm0, xmm0, xmm4					; xmm0 = M1.r[_].z * M2.r[0]
	vaddps xmm1, xmm1, xmm0					; xmm1 = (M1.r[_].x * M2.r[0]) + (M1.r[_].z * M2.r[0])
	vmovss xmm0, dword ptr 12[rcx+r8]
	vshufps xmm0, xmm0, xmm0, 0
	vmulps xmm0, xmm0, xmm5					; xmm0 = M1.r[_].w * M2.r[0]
	vaddps xmm0, xmm2, xmm0					; xmm0 = (M1.r[_].y * M2.r[0]) + (M1.r[_].w * M2.r[0])
	vaddps xmm0, xmm1, xmm0
	vmovups xmmword ptr [rdx+r8], xmm0
	sub r8, 16
	jge _loop
	ret
?XMMatrixMultiply_V3_RegExp2_Impl@@YQXPEBMPEAMT__m128@@222@Z ENDP
_XMMatrixMultiply_V3_RegExp2_Impl ENDS

END
