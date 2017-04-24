#pragma once

#include <sstream>

struct TestCaseEntry
{
	void (*test_case_fun)(const __int32 random_seed, const __int32 num_iterations, std::stringstream& output);

	std::stringstream output;
};

void ProfileMatrixMultiply();
