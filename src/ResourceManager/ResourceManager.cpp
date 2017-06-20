
#include <MemoryLeakDetection.h>

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#pragma comment(lib, "ThreadMessageControlD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#pragma comment(lib, "ThreadMessageControl.lib")
#endif

#include "ResourceManager.h"
#include <ResourceManager\ResoureManagerMessages.h>
#include <Windows.h>
#include <Timer.h>
#include <ThreadMessageControl\ThreadMessageController.h>
namespace MPE
{
	const void T_LoadResource(AssetLoader* loader, Resource* resource)
	{
		loader->LoadResource(resource);

	}


	ResourceManager::ResourceManager(threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime)
	{
	}


	ResourceManager::~ResourceManager()
	{
	
	}
	const void ResourceManager::Start()
	{
		_assetLoaders[0] = DBG_NEW RawAssetLoader("data.dat");
		Timer timer;
		Msg msg;
		bool running = true;
		timer.Start();
		while (running)
		{
			StartProfile;

			// Decode messages. // Only do this if we had time over from the previous frame.
			while (timer.Total<std::chrono::milliseconds>().count() < _frameSyncTime && PeekMsg(msg))
			{
				if (msg.tag == Tag::Shutdown)
					running = false;
				else if (msg.tag == Tag::ResourceManager::LoadResource || msg.tag == Tag::ResourceManager::LoadResourceAndForward)
				{
					LoadResource(msg);
				}
				else if (msg.tag == Tag::ResourceManager::UnloadResource)
				{
					UnloadResource(*(Tag::ResourceManager::UnloadResourceStruct*)msg.data);

				}

				msg.Clean(); // deletes the memory used by msg.
			}

			// Sync with frametime. // TODO: Make sure everything work even if frame took more than frametime.
			auto time = timer.Total<std::chrono::milliseconds>();
			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime) - time);
			timer.Reset();


			// Do general work.
			CheckForResourceFinishedLoading();


			StopProfile;
		}


		for (auto& a : _assetLoaders)
			delete a.second;
		for (auto& r : _resourceRegister)
		{
			delete r.second->data;
			delete r.second;
		}
		_resourceRegister.clear();
	}
	const void ResourceManager::LoadResource(const Msg& msg)
	{

		auto& lrs = *(Tag::ResourceManager::LoadResourceStruct*)msg.data;
		auto load = [this, &lrs, &msg](AssetLoader* loader){
			auto drl = DBG_NEW DiskResourceLoader(lrs.guid, msg.prio);
			if (_diskResourceLoaderQueue.size()) // If there are other resources in the queue we need to resolve priority.
			{
				
				auto top = _diskResourceLoaderQueue.top();
				_diskResourceLoaderQueue.push(drl);
				auto top2 = _diskResourceLoaderQueue.top();
				if (top2 != top)
					top2->thread = std::move(std::thread(T_LoadResource, loader, _resourceRegister[lrs.guid.data]));
			}
			else // Otherwise just push it on the queue and start the thread.
			{
				_diskResourceLoaderQueue.push(drl);
				drl->thread = std::move(std::thread(T_LoadResource, loader, _resourceRegister[lrs.guid.data]));
			}
		};

		auto addNotify = [&msg, &lrs](Resource& r)
		{

			if (msg.tag == Tag::ResourceManager::LoadResource)
			{
				r.toNotify.push({ msg.src, lrs.tag, lrs.prio });
			}
			else
			{
				r.toNotify.push({ lrs.dest, lrs.tag, lrs.prio });
			}
		};

		auto& find = _resourceRegister.find(lrs.guid.data); // Look for the resource in the register
		if (find == _resourceRegister.end()) // If the resource is not in the register, we need to load it.
		{
			_resourceRegister[lrs.guid.data] = DBG_NEW Resource(lrs.guid);
			auto& r = _resourceRegister[lrs.guid.data];

			// Check to see if any of the asset loaders can load this resource. // Should be done in a priority order.
			AssetLoader* loader = nullptr;
			for (auto& a : _assetLoaders)
			{
				if (a.second->IsResourceInRegister(r->guid))
				{
					loader = a.second;
					break;
				}
			}

			if (loader)
			{
				addNotify(*_resourceRegister[lrs.guid.data]);
				load(loader);
			}
			else
			{
				r->state = Resource::ASSET_NOT_FOUND;
			}
		
		}
		else if (find->second->state != Resource::IN_MEMORY && find->second->state != Resource::CURRENTLY_READING) // Or if the resource has been dumped to spare memory we also need to load it.
		{
			
			// Check to see if any of the asset loaders can load this resource. // Should be done in a priority order.
			AssetLoader* loader = nullptr;
			for (auto& a : _assetLoaders)
			{
				if (a.second->IsResourceInRegister(find->second->guid))
				{
					loader = a.second;
					break;
				}
			}

			if (loader)
			{
				addNotify(*_resourceRegister[lrs.guid.data]);
				load(loader);
			}
			else
			{
				find->second->state = Resource::ASSET_NOT_FOUND;
			}
		}

		else	// Send response now.
		{
			auto& r = *_resourceRegister[lrs.guid.data];
			r.usageCount++;
			ThreadMessageController::Send(Tag::ResourceManager::ResouceData::Create(lrs.guid, r.data, r.size, lrs.tag), Destination::ResourceManager, lrs.dest, Tag::ResourceManager::LoadResourceResponse, lrs.prio);
		}



	
	}

	const void ResourceManager::UnloadResource(const Tag::ResourceManager::UnloadResourceStruct & urs)
	{
		auto& find = _resourceRegister.find(urs.guid.data);
		if (find != _resourceRegister.end())
		{
			find->second->usageCount--;
		}
	}

	const void ResourceManager::CheckForResourceFinishedLoading()
	{
		auto join = [this](DiskResourceLoader* drl)
		{
			// Join the thread and pop the job from the queue
			drl->thread.join();
			delete drl;
			_diskResourceLoaderQueue.pop();


			if (_diskResourceLoaderQueue.size()) // If there are more resources resume the top one.
			{
				auto top = _diskResourceLoaderQueue.top();
				auto handle = top->thread.native_handle();
				ResumeThread(handle);
			}

		
		};

		if (_diskResourceLoaderQueue.size())
		{
			auto& drl = _diskResourceLoaderQueue.top();
			auto& resource = *_resourceRegister[drl->guid.data];
			if (resource.state == Resource::IN_MEMORY) // If the resource is now in memory
			{
				join(drl); // Join the thread

				// Send response to all waiting for this resource to load.
				resource.usageCount += resource.toNotify.size();
				auto count = resource.toNotify.size();
				for (int i = 0;i < count; i++)
				{
					auto& top = resource.toNotify.top();

					ThreadMessageController::Send(Tag::ResourceManager::ResouceData::Create(drl->guid, resource.data, resource.size, top.tag), Destination::ResourceManager, top.dest, Tag::ResourceManager::LoadResourceResponse, top.prio);
					delete&top;
					resource.toNotify.pop();
				}
			}
			else if (resource.state == Resource::ASSET_NOT_FOUND)
			{
				printf("***Asset with GUID %llu was not found***\n\n", drl->guid);
				join(drl); // Join the thread
			}
			else if (resource.state == Resource::READ_FAILED)
			{
				printf("***Asset with GUID %llu could not be loaded***\n\n", drl->guid);
				join(drl); // Join the thread
			}

		}

		return void();
	}

}