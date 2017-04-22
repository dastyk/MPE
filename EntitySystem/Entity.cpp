#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif


#include "Entity.h"

#include <random>
#include <thread>

using namespace std;
static thread_local std::random_device rd;  //Will be used to obtain a seed for the random number engine
static thread_local std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
static thread_local std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);
namespace MPE
{
	const uint64_t Entity::GenerateID() 
	{
		StartProfile;
		auto e = dis(gen);
		ProfileReturnConst(e);
	}
}