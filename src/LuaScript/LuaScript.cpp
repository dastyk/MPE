#include "LuaScript.h"
#include "LuaScript_Back.h"

namespace MPE
{
	LuaScript::LuaScript()
	{
	}
	LuaScript * LuaScript::Create(const char * filename)
	{
		return new LuaScript_Back(filename);
	}
	LuaScript::~LuaScript()
	{
	}
}