#ifndef _SCRIPT_PROXY_H_

#pragma once
#include "Entity.h"
namespace MPE
{

	struct EntityProxy
	{
		EntityProxy() : ent() {}
		Entity ent;
		void Test2()
		{
			int i = 0;
		}
	};
	struct SceneProxy
	{

		SceneProxy() {}
		//void AddEntity(sel::Reference<EntityProxy> entity)
		//{
		//	entities.push_back(entity);
		//	int i = 0;
		//}
		//void Clear()
		//{
		//	entities.clear();
		//}
		//std::vector<EntityProxy> entities;
	};

}
#endif // !_SCRIPT_PROXY_H_
