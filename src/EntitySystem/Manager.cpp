#include "Manager.h"

namespace MPE
{


	Manager::Manager(threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime)
	{
	}

	Manager::~Manager() 
	{
	}
}