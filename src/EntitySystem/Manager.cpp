#include "Manager.h"

namespace MPE
{


	Manager::Manager(BaseManagerEntityEntryBlock * entires, threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime), _baseEntityEntires(entires)
	{
	}

	Manager::~Manager() 
	{
	}
}