

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


			if (PeekMsg(msg, Destination::Any, Tag::Any))
			{
				if (msg.tag == Tag::Shutdown)
					running = false;
				else if (msg.tag == Tag::ResourceManager::LoadResource)
				{

				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime));

			StopProfile;
		}
	}
}