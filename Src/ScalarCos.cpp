#include "ScalarCos\ScalarCos.h"
#include <DirectXMath.h>

#include <sstream>

using namespace DirectX;

#include "Utils.h"
#include "ScalarCos\ScalarCos_Ref.h"

// Versions using SSE scalar math
#include "ScalarCos\ScalarCos_SSE_V00.h"

// Versions using FMA scalar math
#include "ScalarCos\ScalarCos_FMA_V00.h"

ScalarCosConstants_SSE_V00 SCALAR_COS_CONSTANTS_SSE_V00 =
{
	XM_PI,
	-XM_PI,
	XM_2PI,
	XM_1DIV2PI,
	XM_PIDIV2,
	-XM_PIDIV2,
	1.0f,
	-1.0f,
	{ -2.6051615e-07f, 2.4760495e-05f, 0.0013888378f, 0.041666638f, 0.5f }
};

ScalarCosConstants_FMA_V00 SCALAR_COS_CONSTANTS_FMA_V00 =
{
	XM_PI,
	-XM_PI,
	XM_2PI,
	XM_1DIV2PI,
	XM_PIDIV2,
	-XM_PIDIV2,
	1.0f,
	-1.0f,
	{ -2.6051615e-07f, 2.4760495e-05f, 0.0013888378f, 0.041666638f, 0.5f }
};

__declspec(noinline) void Test_ScalarCos_Ref(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarCos_Ref(inputs[i]);
	});

	output << "scalar_cos,ref," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarCos_SSE_V00(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarCos_SSE_V00(inputs[i]);
	});

	output << "scalar_cos,sse_v00," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_ScalarCos_FMA_V00(const __int32 num_iterations, std::stringstream& output, const float* inputs, const __int32 num_inputs)
{
	volatile float result = 0.0f;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMScalarCos_FMA_V00(inputs[i]);
	});

	output << "scalar_cos,fma_v00," << TicksToMS(ticks) << std::endl;
}

static void ValidateImplementations(const float input)
{
	const float result_ref = XMScalarCos(input);

	// Binary exact versions
	EnsureFloatEqual(result_ref, XMScalarCos_Ref(input));
	EnsureFloatEqual(result_ref, XMScalarCos_SSE_V00(input));

	// Approximate versions
	constexpr double accuracy_threshold = 0.000001;

	EnsureFloatApproxEqual(result_ref, XMScalarCos_FMA_V00(input), accuracy_threshold);
}

static void WarmUp(const float* inputs, const __int32 num_inputs)
{
	std::stringstream tmp;
	for (__int32 i = 0; i < 1000; ++i) Test_ScalarCos_Ref(100000, tmp, inputs, num_inputs);
}

void ProfileScalarCos()
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

	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarCos_Ref(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarCos_SSE_V00(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_ScalarCos_FMA_V00(num_iterations, output, inputs, num_inputs);

	printf(output.str().c_str());
}
