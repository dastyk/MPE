#ifndef _SCRIPTMANAGER_H_
#define _SCRIPTMANAGER_H_

#pragma once
#include <ThreadMessageControl\Thread.h>
#include <selene.h>

#ifdef _DEBUG
#pragma comment(lib, "ThreadMessageControlD.lib")
#pragma comment(lib, "LuaWrapperD.lib")
#else
#pragma comment(lib, "ThreadMessageControl.lib")
#pragma comment(lib, "LuaWrapper.lib")
#endif
#include <map>

namespace MPE
{
	class ScriptManager : public Thread
	{
		class EntityProxy
		{

		};

	public:
		ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~ScriptManager();

		//! The main entry point for the thread.
		const void Start();


	private:
		sel::State _state;
	};
}
#endif