#include "stdafx.h"
#include <DirectXMath.h>

#include <random>
#include <thread>
#include <sstream>
#include <vector>
#include <conio.h>

using namespace DirectX;

#include "Utils.h"
#include "ScalarSin_Ref.h"
#include "VectorSin_Ref.h"

// 0* versions use C++ scalar math
#include "ScalarSin_V00.h"
#include "ScalarSin_V01.h"
#include "ScalarSin_V02.h"
#include "ScalarSin_V03.h"
#include "ScalarSin_V04.h"
#include "ScalarSin_V05.h"
#include "ScalarSin_V06.h"

// 1* versions use SSE scalar math
#include "ScalarSin_V10.h"
#include "ScalarSin_V11.h"
#include "ScalarSin_V12.h"
#include "ScalarSin_V13.h"
#include "ScalarSin_V14.h"
#include "ScalarSin_V15.h"
#include "ScalarSin_V16.h"
#include "ScalarSin_V17.h"
#include "ScalarSin_V18.h"
#include "ScalarSin_V19.h"

// 2* versions use FMA scalar math
#include "ScalarSin_V20.h"

static std::uniform_real_distribution<float> random_distribution(-1.0, 1.0);
static __int32 random_seed = 304;

ScalarSinConstants_V04 SCALAR_SIN_CONSTANTS_V04 =
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

ScalarSinConstants_V05 SCALAR_SIN_CONSTANTS_V05 =
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

ScalarSinConstants_V06 SCALAR_SIN_CONSTANTS_V06 =
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

ScalarSinConstants_V19 SCALAR_SIN_CONSTANTS_V19 =
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

__declspec(noinline) void Test_ScalarSin_Ref(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_Ref(inputs[i]);
	});

	output << "scalar_sin,ref," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V00(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V00(inputs[i]);
	});

	output << "scalar_sin,v00," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V01(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V01(inputs[i]);
	});

	output << "scalar_sin,v01," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V02(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V02(inputs[i]);
	});

	output << "scalar_sin,v02," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V03(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V03(inputs[i]);
	});

	output << "scalar_sin,v03," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V04(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V04(inputs[i]);
	});

	output << "scalar_sin,v04," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V05(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V05(inputs[i]);
	});

	output << "scalar_sin,v05," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V06(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V06(inputs[i]);
	});

	output << "scalar_sin,v06," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V10(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V10(inputs[i]);
	});

	output << "scalar_sin,v10," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V11(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V11(inputs[i]);
	});

	output << "scalar_sin,v11," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V12(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V12(inputs[i]);
	});

	output << "scalar_sin,v12," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V13(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V13(inputs[i]);
	});

	output << "scalar_sin,v13," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V14(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V14(inputs[i]);
	});

	output << "scalar_sin,v14," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V15(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V15(inputs[i]);
	});

	output << "scalar_sin,v15," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V16(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V16(inputs[i]);
	});

	output << "scalar_sin,v16," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V17(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V17(inputs[i]);
	});

	output << "scalar_sin,v17," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V18(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V18(inputs[i]);
	});

	output << "scalar_sin,v18," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V19(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V19(inputs[i]);
	});

	output << "scalar_sin,v19," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarSin_V20(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarSin_V20(inputs[i]);
	});

	output << "scalar_sin,v20," << TicksToMS(ticks) << std::endl;
}

void ValidateImplementations(const float input)
{
	const float result_ref = XMScalarSin(input);

	// Binary exact versions
	EnsureFloatEqual(result_ref, XMScalarSin_Ref(input));

	EnsureFloatEqual(result_ref, XMScalarSin_V00(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V01(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V02(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V03(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V04(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V05(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V06(input));

	EnsureFloatEqual(result_ref, XMScalarSin_V10(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V11(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V12(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V13(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V14(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V15(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V16(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V17(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V18(input));
	EnsureFloatEqual(result_ref, XMScalarSin_V19(input));

	// Approximate versions
	constexpr double accuracy_threshold = 0.000001;

	EnsureFloatApproxEqual(result_ref, XMScalarSin_V20(input), accuracy_threshold);
}

void ProfileTrigonometry()
{
	const __int32 mask = 1 << 4;
	SetThreadAffinityMask(GetCurrentThread(), mask);

	//constexpr __int32 num_samples = 100;
	constexpr __int32 num_samples = 10;
	constexpr __int32 num_iterations = 100000 * 2;
	//constexpr __int32 num_iterations = 1000;
	constexpr __int32 num_inputs = 128;

	std::random_device rd;
	std::default_random_engine re(rd());
	re.seed(random_seed);

	// Random input in range [-PI, PI]
	float inputs[num_inputs];
	for (__int32 i = 0; i < num_inputs; ++i) inputs[i] = random_distribution(re) * XM_PI * 4;

	// Validate implementations
	for (__int32 i = 0; i < num_inputs; ++i) ValidateImplementations(inputs[i]);

	std::stringstream output;

	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_Ref(random_seed, num_iterations, output, inputs, num_inputs);

	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V00(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V01(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V02(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V03(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V04(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V05(random_seed, num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V06(random_seed, num_iterations, output, inputs, num_inputs);

	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V10(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V11(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V12(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V13(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V14(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V15(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V16(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V17(random_seed, num_iterations, output, inputs, num_inputs);
	//for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V18(random_seed, num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V19(random_seed, num_iterations, output, inputs, num_inputs);

	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarSin_V20(random_seed, num_iterations, output, inputs, num_inputs);

	printf(output.str().c_str());
}

int main()
{
	ProfileTrigonometry();

	if (IsDebuggerPresent())
	{
		printf("Press any key to continue...\n");
		while (_kbhit() == 0);
	}

	return 0;
}
