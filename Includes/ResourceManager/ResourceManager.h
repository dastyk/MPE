#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#pragma once
#include <ThreadMessageControl\Thread.h>

#pragma once
#include <EntitySystem\Entity.h>
#include <unordered_map>

#ifdef _DEBUG
#pragma comment(lib, "ThreadMessageControlD.lib")
#pragma comment(lib, "EntitySystemD.lib")
#else
#pragma comment(lib, "ThreadMessageControl.lib")
#pragma comment(lib, "EntitySystem.lib")
#endif

#include <stack>

namespace MPE
{
	class ResourceManager : public Thread
	{
		struct DiskResourceLoader
		{
			uint8_t priority;
			std::thread thread;		
		};

	public:
		ResourceManager(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~ResourceManager();


		//! The main entry point for the thread.
		const void Start();


	private:
		std::stack<DiskResourceLoader> _diskResourceLoaderStack;
	};
}
#endif