#include "LuaScriptBack.h"
#include  <stdexcept>
//using namespace luabridge;
namespace MPE
{

	LuaScriptBack::LuaScriptBack(const char* filename) 
	{
		/*lua_State* L = luaL_newstate();
		if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) 
		{
			L = 0;
			throw std::runtime_error(std::string("Failed to load srcipt: ") + filename);
		}
		luaL_openlibs(L);

		auto ref = getGlobal(L, "player");
		for (int i = 0; i < ref.length(); i++)
		{

		}*/
	}


	

	LuaScriptBack::~LuaScriptBack()
	{

	}
}