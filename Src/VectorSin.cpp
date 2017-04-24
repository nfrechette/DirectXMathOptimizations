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
	for (__int32 i = 0; i < num_inputs * 4; ++i) input_ptr[i] = random_distribution(re) * XM_PI * 4.0f;

	// Validate implementations
	for (__int32 i = 0; i < num_inputs; ++i) ValidateImplementations(inputs[i]);

	//WarmUp(inputs, num_inputs);
}
