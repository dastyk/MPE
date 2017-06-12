

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif

#include "ResourceManager.h"
#include <ResourceManager\ResoureManagerMessages.h>
#include <Windows.h>
#include <Timer.h>

namespace MPE
{
	const void T_LoadResource(Resource* resource)
	{
		while (true)
		{
			printf("Loading Resource...\n");
		}
	}


	ResourceManager::ResourceManager(AssetLoader* diskAssetLoader, threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime), _diskAssetLoader(diskAssetLoader)
	{
		//	_ASSERT(diskAssetLoader != nullptr);
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

					LoadResource(msg);
				}
				else if (msg.tag == Tag::ResourceManager::LoadResourceAndForward)
				{

				}

				msg.Clean();
			}

			// Sync with frametime. // TOD: Make sure everything work even if frame took more than frametime.
			auto time = timer.Total<std::chrono::milliseconds>();

			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime) - time);
			timer.Reset();




			// Do the work.



			StopProfile;
		}
	}
	const void ResourceManager::LoadResource(const Msg& msg)
	{

		auto& lrs = *(Tag::ResourceManager::LoadResourceStruct*)msg.data;
		auto load = [this, lrs](){
			auto drl = new DiskResourceLoader;
			drl->priority = lrs.priority;
			if (_diskResourceLoaderQueue.size())
			{
				
				auto top = _diskResourceLoaderQueue.top();
				_diskResourceLoaderQueue.push(drl);
				auto top2 = _diskResourceLoaderQueue.top();
				if (top2 != top)
					top2->thread = std::move(std::thread(T_LoadResource, _resourceRegister[lrs.guid.data]));
			}
			else
			{
				_diskResourceLoaderQueue.push(drl);
				drl->thread = std::move(std::thread(T_LoadResource, _resourceRegister[lrs.guid.data]));
			}
		};


		
		auto& find = _resourceRegister.find(lrs.guid.data); // Look for the resource in the register
		if (find == _resourceRegister.end()) // If the resource is not in the register, we need to load it.
			load();
		else if (find->second->state != Resource::IN_MEMORY && find->second->state != Resource::CURRENTLY_READING) // Or if the resource has been dumped to spare memory we also need to load it.
			load();
		else
		{
			// Send response now.
		}
	}

}