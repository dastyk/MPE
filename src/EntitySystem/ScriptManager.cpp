#include "ScriptManager.h"


namespace MPE
{
	using namespace luabridge;
	ScriptManager::ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime) : Manager(identifier, frameSyncTime)
	{
		_script = new LuaScript("data.lua"); // For now we will read from a lua file. Should probably just dump the lua state to a binary file or something.

		getGlobalNamespace(_script->GetState())
			.beginClass<EntityProxy>("EntityProxy")
			.endClass();
	}


	ScriptManager::~ScriptManager()
	{
	}
}