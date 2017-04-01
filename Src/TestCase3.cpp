#include "stdafx.h"
#include "TestCase3.h"

#include <DirectXMath.h>

#include <sstream>

#include "MatrixMultiply_Ref.h"
#include "MatrixMultiply_V0.h"
#include "MatrixMultiply_V1.h"
#include "MatrixMultiply_V2.h"
#include "MatrixMultiply_V3.h"
#include "MatrixMultiply_V4.h"
#include "Utils.h"

using namespace DirectX;

// Test case 3
// 2 local matrices
// Both cannot fit in registers, only 1 of the two

void TestCase3_Setup(const __int32 random_seed, XMMATRIX& mtxA, XMMATRIX& mtxB)
{
	std::random_device rd;
	std::default_random_engine re(rd());
	re.seed(random_seed);

	mtxA = GenerateRandomMatrix(re);
	mtxB = GenerateRandomMatrix(re);
}

__declspec(noinline) void TestCase3_Ref_Reg(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_Ref_Reg(mtxA, mtxB);
		}
	});

	output << "TestCase3,ref_reg," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_Reg2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_Ref_Reg2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,ref_reg2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_RegFlip(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_Ref_RegFlip(mtxA, mtxB);
		}
	});

	output << "TestCase3,ref_regflip," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_RegFlip2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_Ref_RegFlip2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,ref_regflip2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_RegExp(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_Ref_RegExp(mtxA, mtxB);
		}
	});

	output << "TestCase3,ref_regexp," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_RegExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_Ref_RegExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,ref_regexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_Mem(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_Ref_Mem(mtxA, mtxB);
		}
	});

	output << "TestCase3,ref_mem," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_Mem2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_Ref_Mem2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,ref_mem2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_Inl(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_Ref_Inl(mtxA, mtxB);
		}
	});

	output << "TestCase3,ref_inl," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_Inl2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_Ref_Inl2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,ref_inl2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_InlExp(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_Ref_InlExp(mtxA, mtxB);
		}
	});

	output << "TestCase3,ref_inlexp," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_Ref_InlExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_Ref_InlExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,ref_inlexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_Reg(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V0_Reg(mtxA, mtxB);
		}
	});

	output << "TestCase3,v0_reg," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_Reg2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V0_Reg2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v0_reg2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_RegFlip(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V0_RegFlip(mtxA, mtxB);
		}
	});

	output << "TestCase3,v0_regflip," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_RegFlip2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V0_RegFlip2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v0_regflip2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_RegExp(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V0_RegExp(mtxA, mtxB);
		}
	});

	output << "TestCase3,v0_regexp," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_RegExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V0_RegExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v0_regexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_Mem(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V0_Mem(mtxA, mtxB);
		}
	});

	output << "TestCase3,v0_mem," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_Mem2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V0_Mem2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v0_mem2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_Inl(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V0_Inl(mtxA, mtxB);
		}
	});

	output << "TestCase3,v0_inl," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_Inl2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V0_Inl2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v0_inl2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_InlExp(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V0_InlExp(mtxA, mtxB);
		}
	});

	output << "TestCase3,v0_inlexp," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V0_InlExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V0_InlExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v0_inlexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_Reg(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V1_Reg(mtxA, mtxB);
		}
	});

	output << "TestCase3,v1_reg," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_Reg2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V1_Reg2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v1_reg2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_RegFlip(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V1_RegFlip(mtxA, mtxB);
		}
	});

	output << "TestCase3,v1_regflip," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_RegFlip2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V1_RegFlip2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v1_regflip2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_RegExp(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V1_RegExp(mtxA, mtxB);
		}
	});

	output << "TestCase3,v1_regexp," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_RegExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V1_RegExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v1_regexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_Mem(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V1_Mem(mtxA, mtxB);
		}
	});

	output << "TestCase3,v1_mem," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_Mem2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V1_Mem2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v1_mem2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_Inl(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V1_Inl(mtxA, mtxB);
		}
	});

	output << "TestCase3,v1_inl," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_Inl2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V1_Inl2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v1_inl2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_InlExp(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V1_InlExp(mtxA, mtxB);
		}
	});

	output << "TestCase3,v1_inlexp," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V1_InlExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V1_InlExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v1_inlexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_Reg(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V2_Reg(mtxA, mtxB);
		}
	});

	output << "TestCase3,v2_reg," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_Reg2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V2_Reg2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v2_reg2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_RegFlip(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V2_RegFlip(mtxA, mtxB);
		}
	});

	output << "TestCase3,v2_regflip," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_RegFlip2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V2_RegFlip2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v2_regflip2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_RegExp(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V2_RegExp(mtxA, mtxB);
		}
	});

	output << "TestCase3,v2_regexp," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_RegExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V2_RegExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v2_regexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_Mem(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V2_Mem(mtxA, mtxB);
		}
	});

	output << "TestCase3,v2_mem," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_Mem2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V2_Mem2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v2_mem2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_Inl(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V2_Inl(mtxA, mtxB);
		}
	});

	output << "TestCase3,v2_inl," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_Inl2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V2_Inl2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v2_inl2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_InlExp(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			result[mtx_index] = XMMatrixMultiply_V2_InlExp(mtxA, mtxB);
		}
	});

	output << "TestCase3,v2_inlexp," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V2_InlExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V2_InlExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v2_inlexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V3_RegExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V3_RegExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v3_regexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V3_Mem2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V3_Mem2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v3_mem2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V4_RegExp2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V4_RegExp2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v4_regexp2," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void TestCase3_V4_Mem2(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output)
{
	XMMATRIX mtxA;
	XMMATRIX mtxB;
	TestCase3_Setup(random_seed, mtxA, mtxB);

	static XMMATRIX result[64];

	LONGLONG ticks = Measure(num_iterations, [&mtxA, &mtxB]()
	{
		for (__int32 mtx_index = 0; mtx_index < 64; ++mtx_index)
		{
			XMMatrixMultiply_V4_Mem2(mtxA, mtxB, result[mtx_index]);
		}
	});

	output << "TestCase3,v4_mem2," << TicksToMS(ticks) << std::endl;
}

std::vector<TestCaseEntry> GetTestCase3Entries()
{
	std::vector<TestCaseEntry> entries;

	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_Reg });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_Reg2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_RegFlip });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_RegFlip2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_RegExp });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_RegExp2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_Mem });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_Mem2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_Inl });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_Inl2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_InlExp });
	entries.emplace_back(TestCaseEntry{ TestCase3_Ref_InlExp2 });

	entries.emplace_back(TestCaseEntry{ TestCase3_V0_Reg });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_Reg2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_RegFlip });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_RegFlip2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_RegExp });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_RegExp2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_Mem });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_Mem2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_Inl });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_Inl2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_InlExp });
	entries.emplace_back(TestCaseEntry{ TestCase3_V0_InlExp2 });

	entries.emplace_back(TestCaseEntry{ TestCase3_V1_Reg });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_Reg2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_RegFlip });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_RegFlip2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_RegExp });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_RegExp2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_Mem });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_Mem2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_Inl });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_Inl2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_InlExp });
	entries.emplace_back(TestCaseEntry{ TestCase3_V1_InlExp2 });

	entries.emplace_back(TestCaseEntry{ TestCase3_V2_Reg });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_Reg2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_RegFlip });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_RegFlip2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_RegExp });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_RegExp2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_Mem });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_Mem2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_Inl });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_Inl2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_InlExp });
	entries.emplace_back(TestCaseEntry{ TestCase3_V2_InlExp2 });

	entries.emplace_back(TestCaseEntry{ TestCase3_V3_RegExp2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V3_Mem2 });

	entries.emplace_back(TestCaseEntry{ TestCase3_V4_RegExp2 });
	entries.emplace_back(TestCaseEntry{ TestCase3_V4_Mem2 });

	return entries;
}
