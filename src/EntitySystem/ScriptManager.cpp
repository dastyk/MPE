#include "ScriptManager.h"

#include <Profiler.h>
#include <DataManager.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif

namespace MPE
{
	ScriptManager::ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime)
	{

	}


	ScriptManager::~ScriptManager()
	{
	}

	const void ScriptManager::Start()
	{
		_state.Load("data.lua");
		Msg msg;
		bool running = true;
		while (running)
		{
			StartProfile;


			if (PeekMsg(msg, Destination::Any, Tag::Any))
			{
				if (msg.tag == Tag::Shutdown)
					running = false;


				std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime));

				StopProfile;
			}

			return void();
		}
	}
}