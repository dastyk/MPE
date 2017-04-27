#include "ScriptManager.h"


namespace MPE
{
	ScriptManager::ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime) : Manager(nullptr, identifier, frameSyncTime)
	{
		_script = new LuaScript("data.lua"); // For now we will read from a lua file. Should probably just dump the lua state to a binary file or something.


	}


	ScriptManager::~ScriptManager()
	{
	}
}