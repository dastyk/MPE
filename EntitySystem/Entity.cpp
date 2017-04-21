#include "Entity.h"

#include <random>
#include <time.h>
#include <thread>

using namespace std;
static thread_local std::mt19937 generator;
static thread_local std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);

namespace MPE
{
	const uint64_t Entity::GenerateID() 
	{
		return distribution(generator);
	}
}