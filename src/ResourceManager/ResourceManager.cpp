

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif

#include "ResourceManager.h"
#include <ResourceManager\ResoureManagerMessageStructs.h>
#include <Windows.h>
#include <Timer.h>

namespace MPE
{

	const void LoadResource(uint64_t GUID)
	{
		while (true)
		{

		}
	}


	ResourceManager::ResourceManager(threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime)
	{
	}


	ResourceManager::~ResourceManager()
	{
	}
	const void ResourceManager::Start()
	{
		Timer timer;
		Msg msg;
		bool running = true;
		timer.Start();
		while (running)
		{
			StartProfile;

			// Decode messages. // Only do this if we had time over from the previous frame.
			while (timer.Total<std::chrono::milliseconds>().count() < _frameSyncTime && PeekMsg(msg, Destination::Any, Tag::Any))
			{

			
				if (msg.tag == Tag::Shutdown)
					running = false;
				else if (msg.tag == Tag::ResourceManager::LoadResource)
				{
					auto& lrs = *(LoadResourceStruct*)msg.data;
					DiskResourceLoader drl;
					drl.priority = lrs.priority;
					if (_diskResourceLoaderStack.size())
					{
						auto& top = _diskResourceLoaderStack.top();

						if (top.priority < lrs.priority)
						{
							HANDLE h = top.thread.native_handle();
							SuspendThread(h);
							drl.thread = std::move(std::thread(LoadResource, 1234));
							_diskResourceLoaderStack.push(std::move(drl));
						}
						else
						{
							auto temp = std::move(top);
							_diskResourceLoaderStack.pop();
							_diskResourceLoaderStack.push(std::move(drl));
							_diskResourceLoaderStack.push(std::move(temp));
						}
					}
					else
					{
						drl.thread = std::move(std::thread(LoadResource, 1234));
						_diskResourceLoaderStack.push(std::move(drl));
					}
					
				}
				else if (msg.tag == Tag::ResourceManager::LoadResourceAndForward)
				{

				}
			}

			// Sync with frametime. // TOD: Make sure everything work even if frame took more than frametime.
			auto time = timer.Total<std::chrono::milliseconds>();

			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime) - time);
			timer.Reset();




			// Do the work.



			StopProfile;
		}
	}
}