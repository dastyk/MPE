#include "LuaScript.h"
#include "LuaScriptBack.h"

namespace MPE
{
	LuaScript::LuaScript()
	{
	}
	LuaScript * LuaScript::Create(const char * filename)
	{
		return new LuaScriptBack(filename);
	}
	LuaScript::~LuaScript()
	{
	}
}