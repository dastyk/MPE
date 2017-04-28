

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif

#include "ResourceManager.h"

namespace MPE
{

	ResourceManager::ResourceManager(threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime)
	{
	}


	ResourceManager::~ResourceManager()
	{
	}
	const void ResourceManager::Start()
	{
		Msg msg;
		bool running = true;
		while (running)
		{
			StartProfile;


			if (PeekMsg(msg, Msg::Destination::Any, Msg::Tag::Any))
			{
				if (msg.tag == Msg::Tag::Shutdown)
					running = false;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime));

			StopProfile;
		}
	}
}