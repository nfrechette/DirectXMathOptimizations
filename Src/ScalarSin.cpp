#include "ScalarSin.h"
#include <DirectXMath.h>

#include <sstream>

using namespace DirectX;

#include "Utils.h"
#include "ScalarSin_Ref.h"

// Versions using C++ scalar math
#include "ScalarSin_CPP_V00.h"
#include "ScalarSin_CPP_V01.h"
#include "ScalarSin_CPP_V02.h"
#include "ScalarSin_CPP_V03.h"
#include "ScalarSin_CPP_V04.h"
#include "ScalarSin_CPP_V05.h"
#include "ScalarSin_CPP_V06.h"
#include "ScalarSin_CPP_V07.h"

// Versions using SSE scalar math
#include "ScalarSin_SSE_V00.h"
#include "ScalarSin_SSE_V01.h"
#include "ScalarSin_SSE_V02.h"
#include "ScalarSin_SSE_V03.h"
#include "ScalarSin_SSE_V04.h"
#include "ScalarSin_SSE_V05.h"
#include "ScalarSin_SSE_V06.h"
#include "ScalarSin_SSE_V07.h"
#include "ScalarSin_SSE_V08.h"
#include "ScalarSin_SSE_V09.h"
#include "ScalarSin_SSE_V10.h"

// Versions using FMA scalar math
#include "ScalarSin_FMA_V00.h"
#include "ScalarSin_FMA_V01.h"
#include "ScalarSin_FMA_V02.h"
#include "ScalarSin_FMA_V03.h"

ScalarSinConstants_CPP_V05 SCALAR_SIN_CONSTANTS_CPP_V05 =
{
	0.5f,
	-0.5f,
	XM_PI,
	-XM_PI,
	XM_2PI,
	XM_1DIV2PI,
	XM_PIDIV2,
	-XM_PIDIV2,
	{ -2.3889859e-08f, 2.7525562e-06f, 0.00019840874f, 0.0083333310f, 0.16666667f, 1.0f }
};

ScalarSinConstants_CPP_V06 SCALAR_SIN_CONSTANTS_CPP_V06 =
{
	0.0f,
	0.5f,
	-0.5f,
	XM_PI,
	-XM_PI,
	XM_2PI,
	XM_1DIV2PI,
	XM_PIDIV2,
	-XM_PIDIV2,
	{ -2.3889859e-08f, 2.7525562e-06f, 0.00019840874f, 0.0083333310f, 0.16666667f, 1.0f }
};

ScalarSinConstants_CPP_V07 SCALAR_SIN_CONSTANTS_CPP_V07 =
{
	0.5f,
	-0.5f,
	XM_PI,
	-XM_PI,
	XM_2PI,
	XM_1DIV2PI,
	XM_PIDIV2,
	-XM_PIDIV2,
	{ -2.3889859e-08f, 2.7525562e-06f, 0.00019840874f, 0.0083333310f, 0.16666667f, 1.0f }
};

ScalarSinConstants_SSE_V10 SCALAR_SIN_CONSTANTS_SSE_V10 =
{
	XM_PI,
	-XM_PI,
	XM_2PI,
	XM_1DIV2PI,
	XM_PIDIV2,
	-XM_PIDIV2,
	{ -2.3889859e-08f, 2.7525562e-06f, 0.00019840874f, 0.0083333310f, 0.16666667f, 1.0f }
};

ScalarSinConstants_FMA_V03 SCALAR_SIN_CONSTANTS_FMA_V03 =
{
	0.5f,
	XM_PI,
	-XM_PI,
	XM_2PI,
	0x80000000,
	XM_1DIV2PI,
	XM_PIDIV2,
	-XM_PIDIV2,
	{ -2.3889859e-08f, 2.7525562e-06f, 0.00019840874f, 0.0083333310f, 0.16666667f, 1.0f }
};

__declspec(noinline) void Test_ScalarSin_Ref(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_Ref(inputs[i]);
	});

	output << "scalar_sin,ref," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_CPP_V00(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_CPP_V00(inputs[i]);
	});

	output << "scalar_sin,cpp_v00," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_CPP_V01(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_CPP_V01(inputs[i]);
	});

	output << "scalar_sin,cpp_v01," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_CPP_V02(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_CPP_V02(inputs[i]);
	});

	output << "scalar_sin,cpp_v02," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_CPP_V03(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_CPP_V03(inputs[i]);
	});

	output << "scalar_sin,cpp_v03," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_CPP_V04(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_CPP_V04(inputs[i]);
	});

	output << "scalar_sin,cpp_v04," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_CPP_V05(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_CPP_V05(inputs[i]);
	});

	output << "scalar_sin,cpp_v05," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_CPP_V06(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_CPP_V06(inputs[i]);
	});

	output << "scalar_sin,cpp_v06," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_CPP_V07(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_CPP_V07(inputs[i]);
	});

	output << "scalar_sin,cpp_v07," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V00(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V00(inputs[i]);
	});

	output << "scalar_sin,sse_v00," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V01(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V01(inputs[i]);
	});

	output << "scalar_sin,sse_v01," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V02(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V02(inputs[i]);
	});

	output << "scalar_sin,sse_v02," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V03(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V03(inputs[i]);
	});

	output << "scalar_sin,sse_v03," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V04(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V04(inputs[i]);
	});

	output << "scalar_sin,sse_v04," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V05(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V05(inputs[i]);
	});

	output << "scalar_sin,sse_v05," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V06(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V06(inputs[i]);
	});

	output << "scalar_sin,sse_v06," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V07(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V07(inputs[i]);
	});

	output << "scalar_sin,sse_v07," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V08(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V08(inputs[i]);
	});

	output << "scalar_sin,sse_v08," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V09(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V09(inputs[i]);
	});

	output << "scalar_sin,sse_v09," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_SSE_V10(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_SSE_V10(inputs[i]);
	});

	output << "scalar_sin,sse_v10," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_FMA_V00(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_FMA_V00(inputs[i]);
	});

	output << "scalar_sin,fma_v00," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_FMA_V01(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_FMA_V01(inputs[i]);
	});

	output << "scalar_sin,fma_v01," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_FMA_V02(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_FMA_V02(inputs[i]);
	});

	output << "scalar_sin,fma_v02," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_FMA_V03(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_FMA_V03(inputs[i]);
	});

	output << "scalar_sin,fma_v03," << TicksToMS(ticks) << std::endl;
}

void ValidateImplementations(const float input)
{
	const float result_ref = XMScalarSin(input);

	// Binary exact versions
	EnsureFloatEqual(result_ref, XMScalarSin_Ref(input));

	EnsureFloatEqual(result_ref, XMScalarSin_CPP_V00(input));
	EnsureFloatEqual(result_ref, XMScalarSin_CPP_V01(input));
	EnsureFloatEqual(result_ref, XMScalarSin_CPP_V02(input));
	EnsureFloatEqual(result_ref, XMScalarSin_CPP_V03(input));
	EnsureFloatEqual(result_ref, XMScalarSin_CPP_V04(input));
	EnsureFloatEqual(result_ref, XMScalarSin_CPP_V05(input));
	EnsureFloatEqual(result_ref, XMScalarSin_CPP_V06(input));
	EnsureFloatEqual(result_ref, XMScalarSin_CPP_V07(input));

	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V00(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V01(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V02(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V03(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V04(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V05(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V06(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V07(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V08(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V09(input));
	EnsureFloatEqual(result_ref, XMScalarSin_SSE_V10(input));

	// Approximate versions
	constexpr double accuracy_threshold = 0.000001;

	EnsureFloatApproxEqual(result_ref, XMScalarSin_FMA_V00(input), accuracy_threshold);
	EnsureFloatApproxEqual(result_ref, XMScalarSin_FMA_V01(input), accuracy_threshold);
	EnsureFloatApproxEqual(result_ref, XMScalarSin_FMA_V02(input), accuracy_threshold);
	EnsureFloatApproxEqual(result_ref, XMScalarSin_FMA_V03(input), accuracy_threshold);
}

void WarmUp(const float* inputs, const __int32 num_inputs)
{
	std::stringstream tmp;
	for (__int32 i = 0; i < 1000; ++i) Test_ScalarSin_Ref(100000, tmp, inputs, num_inputs);
}

void ProfileScalarSin(const __int32 random_seed, const __int32 num_samples, const __int32 num_iterations)
{
	constexpr __int32 num_inputs = 128;

	std::random_device rd;
	std::default_random_engine re(rd());
	re.seed(random_seed);

	std::uniform_real_distribution<float> random_distribution(-1.0, 1.0);

	// Random input in range [-PI, PI]
	float inputs[num_inputs];

	// Edge cases
	inputs[0] = 0.0f;
	inputs[1] = XM_PIDIV2;
	inputs[2] = XM_PI;
	inputs[3] = XM_PI + XM_PIDIV2;
	inputs[4] = XM_2PI;
	inputs[5] = XM_2PI + XM_PIDIV2;
	inputs[6] = XM_2PI + XM_PI;
	inputs[7] = XM_2PI + XM_PI + XM_PIDIV2;
	inputs[8] = XM_2PI + XM_2PI;
	inputs[9] = -inputs[1];
	inputs[10] = -inputs[2];
	inputs[11] = -inputs[3];
	inputs[12] = -inputs[4];
	inputs[13] = -inputs[5];
	inputs[14] = -inputs[6];
	inputs[15] = -inputs[7];
	inputs[16] = -inputs[8];

	// Random inputs
	for (__int32 i = 17; i < num_inputs; ++i) inputs[i] = random_distribution(re) * XM_PI * 4;

	// Validate implementations
	for (__int32 i = 0; i < num_inputs; ++i) ValidateImplementations(inputs[i]);

	WarmUp(inputs, num_inputs);

	std::stringstream output;

	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_Ref(num_iterations, output, inputs, num_inputs);

	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_CPP_V00(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_CPP_V01(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_CPP_V02(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_CPP_V03(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_CPP_V04(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_CPP_V05(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_CPP_V06(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_CPP_V07(num_iterations, output, inputs, num_inputs);

	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V00(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V01(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V02(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V03(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V04(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V05(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V06(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V07(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V08(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V09(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_SSE_V10(num_iterations, output, inputs, num_inputs);

	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_FMA_V00(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_FMA_V01(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_FMA_V02(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_FMA_V03(num_iterations, output, inputs, num_inputs);

	printf(output.str().c_str());
}
