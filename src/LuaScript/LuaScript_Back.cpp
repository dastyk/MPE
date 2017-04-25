#include "LuaScript_Back.h"
#include  <stdexcept>

namespace MPE
{
	using namespace luabridge;
	LuaScript_Back::LuaScript_Back(const char* filename) : _filename(filename)
	{
		LoadScript(_state, filename);
		/*
		auto ref = getGlobal(L, "player");
		for (int i = 0; i < ref.length(); i++)
		{

		}*/
	}





	

	LuaScript_Back::~LuaScript_Back()
	{

	}
	LuaTable * LuaScript_Back::GetData(const char * tableName)
	{
		if (!_data) _data = new LuaTable_Back(_state);
		return _data;
	}
}