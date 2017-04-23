#include <iostream>
//#include <random>
//int main()
//{
//	std::random_device rd;  //Will be used to obtain a seed for the random number engine
//	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
//	std::uniform_int_distribution<> dis(0, UINT64_MAX);
//
//	
//	uint64_t avg = 0;
//	uint64_t its2 = 0;
//	while (true)
//	{
//		auto first = dis(gen);
//
//		std::random_device rd2;  //Will be used to obtain a seed for the random number engine
//		std::mt19937 gen2(rd2()); //Standard mersenne_twister_engine seeded with rd()
//		std::uniform_int_distribution<> dis2(0, UINT64_MAX);
//		uint64_t its = 0;
//		while (true)
//		{
//			its++;
//			if (first == dis2(gen2))
//			{
//
//				break;
//			}
//		}
//		avg = (avg+ its)/2;
//
//		printf("Found the same random number again after %llu iterations, average %llu\n", its, avg);
//	}
//	getchar();
//}


#if defined( DEBUG ) || defined( _DEBUG )
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif

#include <EntitySystem\DataManager.h>
#include <EntitySystem\DataMangagerMessages.h>
#include <ThreadMessageControl\ThreadMessageController.h>
#include <LuaScript\LuaScript.h>

#ifdef _DEBUG
#pragma comment(lib, "EntitySystemD.lib")
#pragma comment(lib, "LuaScriptD.lib")
#else
#pragma comment(lib, "EntitySystem.lib")
#pragma comment(lib, "LuaScript.lib")
#endif

int main()
{
		#if defined( DEBUG ) || defined( _DEBUG )
			_CrtDumpMemoryLeaks();
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		//	_crtBreakAlloc = 163;
		#endif

	StartProfile;
	MPE::DataManager* dm = new MPE::DataManager(1);
	MPE::ThreadMessageController::Init();

	MPE::ThreadMessageController::StartThread(dm);

	MPE::Entity test;
	MPE::ThreadMessageController::Send(&test, 0, 1, MPE::Tag::DataManager::RegisterEntity);

	MPE::LuaScript* s = MPE::LuaScript::Create("test.lua");


	delete s;

	auto i = 1;
	while (i)
		std::cin >> i;


	MPE::ThreadMessageController::Shutdown();
	delete dm;

	ProfileReturnConst(0);
}