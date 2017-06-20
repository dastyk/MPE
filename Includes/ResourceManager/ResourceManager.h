#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#pragma once
#include <ThreadMessageControl\Thread.h>

#pragma once
#include <EntitySystem\Entity.h>
#include "ResoureManagerMessages.h"
#include <unordered_map>

#ifdef _DEBUG
#pragma comment(lib, "EntitySystemD.lib")
#else
#pragma comment(lib, "EntitySystem.lib")
#endif

#include <queue>
#include "RawAssetLoader.h"
#include <map>
namespace MPE
{
	class ResourceManager : public Thread
	{
		struct DiskResourceLoader
		{
			DiskResourceLoader(const GUID& guid, uint8_t prio = 0) : guid(guid), priority(prio){}
			GUID guid;
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
		ResourceManager(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~ResourceManager();


		//! The main entry point for the thread.
		const void Start();
	private:

		//! Resolve the LoadResource and LoadResourceAndForward message.
		/*!
		It creates a new loading thread if the resourse is not loaded, otherwise a response is sent.
		*/
		const void LoadResource(const Msg& msg);
		//! Resolve the UnloadResource message.
		/*!
		Decreses the usageCount of the given resource.
		*/
		const void UnloadResource(const Tag::ResourceManager::UnloadResourceStruct& urs);

		//! Checks to see if the resource has finished loading.
		const void CheckForResourceFinishedLoading();
	private:
		std::unordered_map<uint64_t, Resource*> _resourceRegister;

		std::priority_queue<DiskResourceLoader*, std::vector<DiskResourceLoader*>, DiskResourceLoaderCompare> _diskResourceLoaderQueue;

		std::map<uint8_t, AssetLoader*> _assetLoaders;
	};
}
#endif