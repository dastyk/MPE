#include "ScriptManager.h"


namespace MPE
{
	ScriptManager::ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime = 16) : Manager(nullptr, identifier, frameSyncTime)
	{
	}


	ScriptManager::~ScriptManager()
	{
	}
}