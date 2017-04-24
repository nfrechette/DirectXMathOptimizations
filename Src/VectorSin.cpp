#include "VectorSin.h"
#include <DirectXMath.h>

#include <sstream>

using namespace DirectX;

#include "Utils.h"
#include "VectorSin_Ref.h"

void XM_CALLCONV ValidateImplementations(const XMVECTOR input)
{
	const XMVECTOR result_ref = XMVectorSin(input);

	// Binary exact versions
	EnsureVectorEqual(result_ref, XMVectorSin_Ref(input));
}

void ProfileVectorSin(const __int32 random_seed, const __int32 num_samples, const __int32 num_iterations)
{
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

	//WarmUp(inputs, num_inputs);
}
