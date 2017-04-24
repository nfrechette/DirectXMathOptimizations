#include "stdafx.h"
#include <DirectXMath.h>

#include <random>
#include <thread>
#include <sstream>
#include <vector>
#include <conio.h>

#include "MatrixMultiply\MatrixMultiply_Ref.h"
#include "MatrixMultiply\MatrixMultiply_V0.h"
#include "MatrixMultiply\MatrixMultiply_V1.h"
#include "MatrixMultiply\MatrixMultiply_V2.h"
#include "MatrixMultiply\MatrixMultiply_V3.h"
#include "MatrixMultiply\MatrixMultiply_V4.h"
#include "Utils.h"

#include "MatrixMultiply\TestCase1.h"
#include "MatrixMultiply\TestCase2.h"
#include "MatrixMultiply\TestCase3.h"

enum class TestCaseExecution
{
	Sync,						// Single threaded
	Async_PerCore,				// 1 thread per physical core (max 3)
	Async_Saturate,				// 1 thread per logical core (max 4)
};

using namespace DirectX;

// We always test the following cases:
//		ref_reg: reference with FXMMATRIX as first argument
//		ref_mem: reference with CXMMATRIX as first argument if applicable
//		ref_inl: reference force inline
//		opt_reg: opt impl with FXMMATRIX as first argument
//		opt_mem: opt impl with CXMMATRIX as first argument
//		opt_inl: opt impl force inline

static std::uniform_real_distribution<float> random_distribution(-1.0, 1.0);
static __int32 random_seed = 304;

XMMATRIX GenerateRandomMatrix(std::default_random_engine& re)
{
	const float pitch = random_distribution(re) * 90.0f;
	const float yaw = random_distribution(re) * 90.0f;
	const float roll = random_distribution(re) * 90.0f;

	const float pos_x = random_distribution(re) * 200.0f;
	const float pos_y = random_distribution(re) * 200.0f;
	const float pos_z = random_distribution(re) * 200.0f;

	XMVECTOR quat = XMQuaternionRotationRollPitchYaw(DegToRad(pitch), DegToRad(yaw), DegToRad(roll));
	XMVECTOR pos = XMVectorSet(pos_x, pos_y, pos_z, 1.0f);

	XMMATRIX result;
	result = XMMatrixRotationQuaternion(quat);
	result.r[3] = pos;
	return result;
}

void ValidateImplementations()
{
	const XMVECTOR quat0 = XMQuaternionRotationRollPitchYaw(DegToRad(32.0f), DegToRad(78.0f), DegToRad(13.0f));
	const XMVECTOR quat1 = XMQuaternionRotationRollPitchYaw(DegToRad(87.0f), DegToRad(23.0f), DegToRad(43.0f));

	const XMVECTOR pos0 = XMVectorSet(293.0f, 581.0f, 0.004f, 1.0f);
	const XMVECTOR pos1 = XMVectorSet(526.0f, 1135, 0.1234f, 1.0f);

	XMMATRIX mtx0 = XMMatrixRotationQuaternion(quat0);
	mtx0.r[3] = pos0;

	XMMATRIX mtx1 = XMMatrixRotationQuaternion(quat1);
	mtx0.r[3] = pos1;

	const XMMATRIX ref_mtx = XMMatrixMultiply(mtx0, mtx1);
	XMMATRIX tmp_mtx;

	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_Ref_Reg(mtx0, mtx1));
	XMMatrixMultiply_Ref_Reg2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_Ref_RegFlip(mtx0, mtx1));
	XMMatrixMultiply_Ref_RegFlip2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_Ref_RegExp(mtx0, mtx1));
	XMMatrixMultiply_Ref_RegExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_Ref_Mem(mtx0, mtx1));
	XMMatrixMultiply_Ref_Mem2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_Ref_Inl(mtx0, mtx1));
	XMMatrixMultiply_Ref_Inl2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_Ref_InlExp(mtx0, mtx1));
	XMMatrixMultiply_Ref_InlExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);

	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V0_Reg(mtx0, mtx1));
	XMMatrixMultiply_V0_Reg2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V0_RegFlip(mtx0, mtx1));
	XMMatrixMultiply_V0_RegFlip2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V0_RegExp(mtx0, mtx1));
	XMMatrixMultiply_V0_RegExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V0_Mem(mtx0, mtx1));
	XMMatrixMultiply_V0_Mem2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V0_Inl(mtx0, mtx1));
	XMMatrixMultiply_V0_Inl2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V0_InlExp(mtx0, mtx1));
	XMMatrixMultiply_V0_InlExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);

	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V1_Reg(mtx0, mtx1));
	XMMatrixMultiply_V1_Reg2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V1_RegFlip(mtx0, mtx1));
	XMMatrixMultiply_V1_RegFlip2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V1_RegExp(mtx0, mtx1));
	XMMatrixMultiply_V1_RegExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V1_Mem(mtx0, mtx1));
	XMMatrixMultiply_V1_Mem2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V1_Inl(mtx0, mtx1));
	XMMatrixMultiply_V1_Inl2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V1_InlExp(mtx0, mtx1));
	XMMatrixMultiply_V1_InlExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);

	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V2_Reg(mtx0, mtx1));
	XMMatrixMultiply_V2_Reg2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V2_RegFlip(mtx0, mtx1));
	XMMatrixMultiply_V2_RegFlip2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V2_RegExp(mtx0, mtx1));
	XMMatrixMultiply_V2_RegExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V2_Mem(mtx0, mtx1));
	XMMatrixMultiply_V2_Mem2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V2_Inl(mtx0, mtx1));
	XMMatrixMultiply_V2_Inl2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	EnsureMatrixEqual(ref_mtx, XMMatrixMultiply_V2_InlExp(mtx0, mtx1));
	XMMatrixMultiply_V2_InlExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);

	XMMatrixMultiply_V3_RegExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	XMMatrixMultiply_V3_Mem2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);

	XMMatrixMultiply_V4_RegExp2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
	XMMatrixMultiply_V4_Mem2(mtx0, mtx1, tmp_mtx); EnsureMatrixEqual(ref_mtx, tmp_mtx);
}

struct TestCaseSuite
{
	std::vector<TestCaseEntry> entries;
};

static void Execute_Sync(std::vector<TestCaseSuite>& test_cases, const __int32 random_seed, const __int32 num_samples, const __int32 num_iterations)
{
	const __int32 mask = 1 << 0;
	SetThreadAffinityMask(GetCurrentThread(), mask);

	for (TestCaseSuite& test_case : test_cases)
	{
		for (TestCaseEntry& entry : test_case.entries)
		{
			for (__int32 i = 0; i < num_samples; ++i)
				(*entry.test_case_fun)(random_seed, num_iterations, entry.output);
		}

		for (const TestCaseEntry& entry : test_case.entries)
			printf(entry.output.str().c_str());
	}
}

static void Execute_Async_PerCore(std::vector<TestCaseSuite>& test_cases, const __int32 random_seed, const __int32 num_samples, const __int32 num_iterations)
{
	std::vector<TestCaseEntry*> entries;
	for (TestCaseSuite& test_case : test_cases)
	{
		for (TestCaseEntry& entry : test_case.entries)
			entries.emplace_back(&entry);
	}

	constexpr __int32 num_threads = 3;
	const size_t num_entries_per_thread = (entries.size() + num_threads - 1) / num_threads;

	auto thread_start_it = entries.begin();
	auto entries_end_it = entries.end();

	std::vector<std::thread> threads;

	for (__int32 thread_index = 0; thread_index < num_threads; ++thread_index)
	{
		auto thread_end_it = thread_start_it + num_entries_per_thread;

		threads.emplace_back(std::thread([=]() {
			const __int32 mask = 1 << (thread_index * 2);
			SetThreadAffinityMask(GetCurrentThread(), mask);

			for (auto it = thread_start_it; it != thread_end_it && it != entries_end_it; ++it)
			{
				TestCaseEntry& entry = **it;

				for (__int32 i = 0; i < num_samples; ++i)
					(*entry.test_case_fun)(random_seed, num_iterations, entry.output);
			}
		}));

		thread_start_it = thread_end_it;
	}

	for (std::thread& thread : threads)
		thread.join();

	for (TestCaseSuite& test_case : test_cases)
	{
		for (const TestCaseEntry& entry : test_case.entries)
			printf(entry.output.str().c_str());
	}
}

static void Execute_Async_Saturate(std::vector<TestCaseSuite>& test_cases, const __int32 random_seed, const __int32 num_samples, const __int32 num_iterations)
{
	std::vector<TestCaseEntry*> entries;
	for (TestCaseSuite& test_case : test_cases)
	{
		for (TestCaseEntry& entry : test_case.entries)
			entries.emplace_back(&entry);
	}

	constexpr __int32 num_threads = 4;
	const size_t num_entries_per_thread = (entries.size() + num_threads - 1) / num_threads;

	auto thread_start_it = entries.begin();
	auto entries_end_it = entries.end();

	std::vector<std::thread> threads;

	for (__int32 thread_index = 0; thread_index < num_threads; ++thread_index)
	{
		auto thread_end_it = thread_start_it + num_entries_per_thread;

		threads.emplace_back(std::thread([=]() {
			const __int32 mask = 1 << thread_index;
			SetThreadAffinityMask(GetCurrentThread(), mask);

			for (auto it = thread_start_it; it != thread_end_it && it != entries_end_it; ++it)
			{
				TestCaseEntry& entry = **it;

				for (__int32 i = 0; i < num_samples; ++i)
					(*entry.test_case_fun)(random_seed, num_iterations, entry.output);
			}
		}));

		thread_start_it = thread_end_it;
	}

	for (std::thread& thread : threads)
		thread.join();

	for (TestCaseSuite& test_case : test_cases)
	{
		for (const TestCaseEntry& entry : test_case.entries)
			printf(entry.output.str().c_str());
	}
}

void ProfileMatrixMultiply()
{
	ValidateImplementations();

	constexpr __int32 num_samples = 100;
	//constexpr __int32 num_samples = 1;
	constexpr __int32 num_iterations = 1000000;
	//constexpr __int32 num_iterations = 1000;

	// Note that enabling multi threading is handy for quick testing but the results will vary.
	// All the test cases write to arrays which will stress the memory bandwidth which can slow things down a bit.
	constexpr TestCaseExecution execution = TestCaseExecution::Sync;

	std::vector<TestCaseSuite> test_cases;
	test_cases.push_back(TestCaseSuite{ GetTestCase1Entries() });
	test_cases.push_back(TestCaseSuite{ GetTestCase2Entries() });
	test_cases.push_back(TestCaseSuite{ GetTestCase3Entries() });

	switch (execution)
	{
		case TestCaseExecution::Sync:
			Execute_Sync(test_cases, random_seed, num_samples, num_iterations);
			break;
		case TestCaseExecution::Async_PerCore:
			Execute_Async_PerCore(test_cases, random_seed, num_samples, num_iterations);
			break;
		case TestCaseExecution::Async_Saturate:
			Execute_Async_Saturate(test_cases, random_seed, num_samples, num_iterations);
			break;
	}
}

int main()
{
	ProfileMatrixMultiply();

	if (IsDebuggerPresent())
	{
		printf("Press any key to continue...\n");
		while (_kbhit() == 0);
	}

	return 0;
}
