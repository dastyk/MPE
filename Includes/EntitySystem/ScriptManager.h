#ifndef _SCRIPTMANAGER_H_
#define _SCRIPTMANAGER_H_

#pragma once
#include <ThreadMessageControl\Thread.h>
#include "Manager.h"
#include <selene.h>
#include "Entity.h"
#include "ScriptProxy.h"

#ifdef _DEBUG
#pragma comment(lib, "LuaD.lib")
#else
#pragma comment(lib, "Lua.lib")
#endif
#include <map>

namespace MPE
{

	class ScriptManager : public Thread
	{

	public:
		ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~ScriptManager();

		//! The main entry point for the thread.
		const void Start();

		//! Registers a manager
		const void RegisterManager(Manager* manager);

		//! Register many manager as once
		const void RegisterManager(const std::vector <Manager*>& managers);


		//! 
		void CreateScene(sel::Reference<SceneProxy> scene);


	private:

	private:
		sel::State _state;

		std::vector<Manager*> _entityManagers;

	};
}
#endif