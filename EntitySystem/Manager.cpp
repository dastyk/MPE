#include "Manager.h"

namespace MPE
{


	Manager::Manager(BaseManagerEntityEntryBlock * entires) : Thread(), _baseEntityEntires(entires)
	{
	}

	Manager::~Manager() 
	{
	}
}