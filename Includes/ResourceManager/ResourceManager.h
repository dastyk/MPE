#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#pragma once
#include <ThreadMessageControl\Thread.h>

#pragma once
#include <EntitySystem\Entity.h>
#include "ResoureManagerMessages.h"
#include <unordered_map>

#ifdef _DEBUG
#pragma comment(lib, "ThreadMessageControlD.lib")
#pragma comment(lib, "EntitySystemD.lib")
#else
#pragma comment(lib, "ThreadMessageControl.lib")
#pragma comment(lib, "EntitySystem.lib")
#endif

#include <queue>
#include "AssetLoader.h"

namespace MPE
{
	class ResourceManager : public Thread
	{
		struct DiskResourceLoader
		{
			uint8_t priority;
			std::thread thread;		
		};
		class DiskResourceLoaderCompare
		{
		public:
			bool operator() (DiskResourceLoader* l, DiskResourceLoader* r)
			{
				return l->priority < r->priority;
			}
		};
	public:
		ResourceManager(AssetLoader* diskAssetLoader, threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~ResourceManager();


		//! The main entry point for the thread.
		const void Start();
	private:
		const void LoadResource(const Msg& msg);

	private:
		std::unordered_map<uint64_t, Resource*> _resourceRegister;

		std::priority_queue<DiskResourceLoader*, std::vector<DiskResourceLoader*>, DiskResourceLoaderCompare> _diskResourceLoaderQueue;

		AssetLoader* _diskAssetLoader;
	};
}
#endif