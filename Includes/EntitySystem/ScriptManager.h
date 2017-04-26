#ifndef _SCRIPTMANAGER_H_
#define _SCRIPTMANAGER_H_
#pragma once
#include "Manager.h"
namespace MPE
{
	class ScriptManager :
		public Manager
	{
	public:
		ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~ScriptManager();
	};

}

#endif