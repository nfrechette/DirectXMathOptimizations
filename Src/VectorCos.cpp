#include "VectorCos\VectorCos.h"
#include <DirectXMath.h>

#include <sstream>

using namespace DirectX;

#include "Utils.h"
#include "VectorCos\VectorCos_Ref.h"

// Versions using C++ scalar math
//#include "ScalarSin\ScalarSin_CPP_V00.h"

// Versions using SSE scalar math
//#include "ScalarSin\ScalarSin_SSE_V00.h"

// Versions using FMA scalar math
//#include "ScalarSin\ScalarSin_FMA_V00.h"

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

static void ValidateImplementations(const XMVECTOR input)
{
	const XMVECTOR result_ref = XMVectorCos(input);

	// Binary exact versions
	EnsureVectorEqual(result_ref, XMVectorCos_Ref(input));
}

static void WarmUp(const XMVECTOR* inputs, const __int32 num_inputs)
{
	std::stringstream tmp;
	for (__int32 i = 0; i < 1000; ++i) Test_VectorCos_Ref(100000, tmp, inputs, num_inputs);
}

void ProfileVectorCos()
{
}
