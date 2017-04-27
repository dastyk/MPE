#include "ScriptManager.h"


namespace MPE
{
	ScriptManager::ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime) : Manager(nullptr, identifier, frameSyncTime)
	{
	}


	ScriptManager::~ScriptManager()
	{
	}
}