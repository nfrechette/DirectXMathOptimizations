#include "VectorSin\VectorSin.h"
#include <DirectXMath.h>

#include <sstream>

using namespace DirectX;

#include "Utils.h"
#include "VectorSin\VectorSin_Ref.h"

// Versions using SSE scalar math
#include "VectorSin\VectorSin_SSE_V00.h"
#include "VectorSin\VectorSin_SSE_V01.h"
#include "VectorSin\VectorSin_SSE_V02.h"
#include "VectorSin\VectorSin_SSE_V03.h"
#include "VectorSin\VectorSin_SSE_V04.h"
#include "VectorSin\VectorSin_SSE_V05.h"
#include "VectorSin\VectorSin_SSE_V06.h"
#include "VectorSin\VectorSin_SSE_V07.h"
#include "VectorSin\VectorSin_SSE_V08.h"

// Versions using FMA scalar math
#include "VectorSin\VectorSin_FMA_V00.h"
#include "VectorSin\VectorSin_FMA_V01.h"

VectorSinConstants_SSE_V04 VECTOR_SIN_CONSTANTS_SSE_V04 =
{
	g_XMPi,
	g_XMTwoPi,
	g_XMNegativeZero,
	g_XMReciprocalTwoPi,
	g_XMHalfPi,
	{
		{ -2.3889859e-08f, -2.3889859e-08f, -2.3889859e-08f, -2.3889859e-08f },
		{ 2.7525562e-06f, 2.7525562e-06f, 2.7525562e-06f, 2.7525562e-06f },
		{ -0.00019840874f, -0.00019840874f, -0.00019840874f, -0.00019840874f },
		{ 0.0083333310f, 0.0083333310f, 0.0083333310f, 0.0083333310f },
		{ -0.16666667f, -0.16666667f, -0.16666667f, -0.16666667f },
		{ 1.0f, 1.0f, 1.0f, 1.0f }
	}
};

VectorSinConstants_SSE_V05 VECTOR_SIN_CONSTANTS_SSE_V05 =
{
	g_XMReciprocalTwoPi,
	XM_PI,
	XM_2PI,
	*(float*)&g_XMNegativeZero,
	XM_PIDIV2,
	{
		{ -2.3889859e-08f, -2.3889859e-08f, -2.3889859e-08f, -2.3889859e-08f },
		{ 2.7525562e-06f, 2.7525562e-06f, 2.7525562e-06f, 2.7525562e-06f },
		{ -0.00019840874f, -0.00019840874f, -0.00019840874f, -0.00019840874f },
		{ 0.0083333310f, 0.0083333310f, 0.0083333310f, 0.0083333310f },
		{ -0.16666667f, -0.16666667f, -0.16666667f, -0.16666667f },
		{ 1.0f, 1.0f, 1.0f, 1.0f }
	}
};

VectorSinConstants_SSE_V06 VECTOR_SIN_CONSTANTS_SSE_V06 =
{
	g_XMReciprocalTwoPi,
	XM_PI,
	XM_2PI,
	*(float*)&g_XMNegativeZero,
	XM_PIDIV2,
	{
		-2.3889859e-08f,
		2.7525562e-06f,
		-0.00019840874f,
		0.0083333310f,
		-0.16666667f,
		1.0f
	}
};

VectorSinConstants_SSE_V07 VECTOR_SIN_CONSTANTS_SSE_V07 =
{
	g_XMReciprocalTwoPi,
	{ -2.3889859e-08f, 2.7525562e-06f, -0.00019840874f, 0.0083333310f },
	{ -0.16666667f, 1.0f, 0.0f, 0.0f },
	XM_PI,
	XM_2PI,
	*(float*)&g_XMNegativeZero,
	XM_PIDIV2
};

VectorSinConstants_SSE_V08 VECTOR_SIN_CONSTANTS_SSE_V08 =
{
	g_XMReciprocalTwoPi,
	{ *(float*)&g_XMNegativeZero, XM_PI, -2.3889859e-08f, 2.7525562e-06f },
	{ -0.00019840874f, 0.0083333310f, -0.16666667f, 1.0f },
	XM_2PI,
	XM_PIDIV2
};

VectorSinConstants_FMA_V01 VECTOR_SIN_CONSTANTS_FMA_V01 =
{
	g_XMPi,
	g_XMTwoPi,
	g_XMNegativeZero,
	g_XMReciprocalTwoPi,
	g_XMHalfPi,
	{
		{ -2.3889859e-08f, -2.3889859e-08f, -2.3889859e-08f, -2.3889859e-08f },
		{ 2.7525562e-06f, 2.7525562e-06f, 2.7525562e-06f, 2.7525562e-06f },
		{ -0.00019840874f, -0.00019840874f, -0.00019840874f, -0.00019840874f },
		{ 0.0083333310f, 0.0083333310f, 0.0083333310f, 0.0083333310f },
		{ -0.16666667f, -0.16666667f, -0.16666667f, -0.16666667f },
		{ 1.0f, 1.0f, 1.0f, 1.0f }
	}
};

__declspec(noinline) void Test_VectorSin_Ref(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_Ref(inputs[i]);
	});

	output << "vector_sin,ref," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V00(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V00(inputs[i]);
	});

	output << "vector_sin,sse_v00," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V01(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V01(inputs[i]);
	});

	output << "vector_sin,sse_v01," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V02(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V02(inputs[i]);
	});

	output << "vector_sin,sse_v02," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V03(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V03(inputs[i]);
	});

	output << "vector_sin,sse_v03," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V04(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V04(inputs[i]);
	});

	output << "vector_sin,sse_v04," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V05(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V05(inputs[i]);
	});

	output << "vector_sin,sse_v05," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V06(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V06(inputs[i]);
	});

	output << "vector_sin,sse_v06," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V07(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V07(inputs[i]);
	});

	output << "vector_sin,sse_v07," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_SSE_V08(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_SSE_V08(inputs[i]);
	});

	output << "vector_sin,sse_v08," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_FMA_V00(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_FMA_V00(inputs[i]);
	});

	output << "vector_sin,fma_v00," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorSin_FMA_V01(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorSin_FMA_V01(inputs[i]);
	});

	output << "vector_sin,fma_v01," << TicksToMS(ticks) << std::endl;
}

void XM_CALLCONV ValidateImplementations(const XMVECTOR& input)
{
	const XMVECTOR result_ref = XMVectorSin(input);

	// Binary exact versions
	EnsureVectorEqual(result_ref, XMVectorSin_Ref(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V00(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V01(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V02(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V03(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V04(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V05(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V06(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V07(input));
	EnsureVectorEqual(result_ref, XMVectorSin_SSE_V08(input));

	// Approximate versions
	constexpr double accuracy_threshold = 0.000001;

	EnsureVectorApproxEqual(result_ref, XMVectorSin_FMA_V00(input), accuracy_threshold);
	EnsureVectorApproxEqual(result_ref, XMVectorSin_FMA_V01(input), accuracy_threshold);
}

void WarmUp(const XMVECTOR* inputs, const __int32 num_inputs)
{
	std::stringstream tmp;
	for (__int32 i = 0; i < 250; ++i) Test_VectorSin_Ref(100000, tmp, inputs, num_inputs);
}

void ProfileVectorSin()
{
	//constexpr __int32 num_samples = 100;
	constexpr __int32 num_samples = 10;

	constexpr __int32 num_iterations = 100000 * 2;
	//constexpr __int32 num_iterations = 1000;

	constexpr __int32 random_seed = 304;
	constexpr __int32 num_inputs = 128;

	std::random_device rd;
	std::default_random_engine re(rd());
	re.seed(random_seed);

	std::uniform_real_distribution<float> random_distribution(-1.0f, 1.0f);

	// Random input in range [-PI, PI]
	XMVECTOR inputs[num_inputs];
	float* input_ptr = (float*)&inputs[0];

	// Edge cases
	input_ptr[0] = 0.0f;
	input_ptr[1] = XM_PIDIV2;
	input_ptr[2] = XM_PI;
	input_ptr[3] = XM_PI + XM_PIDIV2;
	input_ptr[4] = XM_2PI;
	input_ptr[5] = XM_2PI + XM_PIDIV2;
	input_ptr[6] = XM_2PI + XM_PI;
	input_ptr[7] = XM_2PI + XM_PI + XM_PIDIV2;
	input_ptr[8] = XM_2PI + XM_2PI;
	input_ptr[9] = -input_ptr[1];
	input_ptr[10] = -input_ptr[2];
	input_ptr[11] = -input_ptr[3];
	input_ptr[12] = -input_ptr[4];
	input_ptr[13] = -input_ptr[5];
	input_ptr[14] = -input_ptr[6];
	input_ptr[15] = -input_ptr[7];
	input_ptr[16] = -input_ptr[8];

	// Random inputs
	for (__int32 i = 17; i < (num_inputs * 4); ++i) input_ptr[i] = random_distribution(re) * XM_PI * 4.0f;

	// Validate implementations
	for (__int32 i = 0; i < num_inputs; ++i) ValidateImplementations(inputs[i]);

	WarmUp(inputs, num_inputs);

	std::stringstream output;

	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_Ref(num_iterations, output, inputs, num_inputs);

	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V00(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V01(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V02(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V03(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V04(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V05(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V06(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V07(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_SSE_V08(num_iterations, output, inputs, num_inputs);

	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_FMA_V00(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorSin_FMA_V01(num_iterations, output, inputs, num_inputs);

	printf(output.str().c_str());
}
