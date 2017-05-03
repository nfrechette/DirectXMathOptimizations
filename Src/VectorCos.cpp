#include "VectorCos\VectorCos.h"
#include <DirectXMath.h>

#include <sstream>

using namespace DirectX;

#include "Utils.h"
#include "VectorCos\VectorCos_Ref.h"

// Versions using SSE scalar math
#include "VectorCos\VectorCos_SSE_V00.h"

// Versions using FMA scalar math
#include "VectorCos\VectorCos_FMA_V00.h"

VectorCosConstants_SSE_V00 VECTOR_COS_CONSTANTS_SSE_V00 =
{
	g_XMReciprocalTwoPi,
	g_XMTwoPi,
	g_XMNegativeZero,
	g_XMPi,
	g_XMHalfPi,
	g_XMOne,
	g_XMNegativeOne,
	{
		{ -2.6051615e-07f, -2.6051615e-07f, -2.6051615e-07f, -2.6051615e-07f },
		{ 2.4760495e-05f, 2.4760495e-05f, 2.4760495e-05f, 2.4760495e-05f },
		{ -0.0013888378f, -0.0013888378f, -0.0013888378f, -0.0013888378f },
		{ 0.041666638f, 0.041666638f, 0.041666638f, 0.041666638f },
		{ -0.5f, -0.5f, -0.5f, -0.5f },
	}
};

VectorCosConstants_FMA_V00 VECTOR_COS_CONSTANTS_FMA_V00 =
{
	g_XMReciprocalTwoPi,
	g_XMTwoPi,
	g_XMNegativeZero,
	g_XMPi,
	g_XMHalfPi,
	g_XMOne,
	g_XMNegativeOne,
	{
		{ -2.6051615e-07f, -2.6051615e-07f, -2.6051615e-07f, -2.6051615e-07f },
		{ 2.4760495e-05f, 2.4760495e-05f, 2.4760495e-05f, 2.4760495e-05f },
		{ -0.0013888378f, -0.0013888378f, -0.0013888378f, -0.0013888378f },
		{ 0.041666638f, 0.041666638f, 0.041666638f, 0.041666638f },
		{ -0.5f, -0.5f, -0.5f, -0.5f },
	}
};

__declspec(noinline) void Test_VectorCos_Ref(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorCos_Ref(inputs[i]);
	});

	output << "vector_cos,ref," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorCos_SSE_V00(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorCos_SSE_V00(inputs[i]);
	});

	output << "vector_cos,sse_v00," << TicksToMS(ticks) << std::endl;
}

__declspec(noinline) void Test_VectorCos_FMA_V00(const __int32 num_iterations, std::stringstream& output, const XMVECTOR* inputs, const __int32 num_inputs)
{
	XMVECTOR result;

	LONGLONG ticks = Measure(num_iterations, [inputs, num_inputs, &result]()
	{
		for (__int32 i = 0; i < num_inputs; ++i)
			result = XMVectorCos_FMA_V00(inputs[i]);
	});

	output << "vector_cos,fma_v00," << TicksToMS(ticks) << std::endl;
}

static void ValidateImplementations(const XMVECTOR input)
{
	const XMVECTOR result_ref = XMVectorCos(input);

	// Binary exact versions
	EnsureVectorEqual(result_ref, XMVectorCos_Ref(input));
	EnsureVectorEqual(result_ref, XMVectorCos_SSE_V00(input));

	// Approximate versions
	constexpr double accuracy_threshold = 0.000001;

	EnsureVectorApproxEqual(result_ref, XMVectorCos_FMA_V00(input), accuracy_threshold);
}

static void WarmUp(const XMVECTOR* inputs, const __int32 num_inputs)
{
	std::stringstream tmp;
	for (__int32 i = 0; i < 1000; ++i) Test_VectorCos_Ref(100000, tmp, inputs, num_inputs);
}

void ProfileVectorCos()
{
	//constexpr __int32 num_samples = 100;
	constexpr __int32 num_samples = 10;

	constexpr __int32 num_iterations = 100000 * 2;
	//constexpr __int32 num_iterations = 1000;

	constexpr __int32 random_seed = 304;
	constexpr __int32 num_inputs = 512;

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

	for (__int32 i = 0; i < num_samples; ++i) Test_VectorCos_Ref(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorCos_SSE_V00(num_iterations, output, inputs, num_inputs);
	for (__int32 i = 0; i < num_samples; ++i) Test_VectorCos_FMA_V00(num_iterations, output, inputs, num_inputs);

	printf(output.str().c_str());
}
