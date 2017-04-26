#include "LuaScript_Back.h"
#include  <stdexcept>

namespace MPE
{
	using namespace luabridge;
	LuaScript_Back::LuaScript_Back(const char* filename) : _filename(filename) , _data(nullptr), _state(nullptr)
	{
		LuaHelpers::LoadScript(_state, filename);
		/*
		auto ref = getGlobal(L, "player");
		for (int i = 0; i < ref.length(); i++)
		{

		}*/
	}





	

	LuaScript_Back::~LuaScript_Back()
	{	
		delete _data;
		lua_close(_state);
	}
	LuaTable * LuaScript_Back::GetTable(const char * tableName)
	{
		if (!_data) _data = new LuaTable_Back(_state, tableName);
		return _data;
	}
	const void LuaScript_Back::LoadScript(const char * filename)
	{
		LuaHelpers::LoadScript(_state, filename);
	}
}