#ifndef _LUA_SCRIPT_H_
#define  _LUA_SCRIPT_H_
#pragma once

namespace MPE
{
	//! A pure virtual class, so we can avoid including the base lua src into the whole thing.
	/*!
	This class hides the actual lua implementation found in LuaScriptBack
	\sa LuaScriptBack
	*/
	class LuaScript
	{
	protected:
		//! Protected Constructor
		LuaScript();

	public:
		//! Creates the actual LuaScriptBack object.
		static LuaScript* Create(const char* filename);
		virtual ~LuaScript();


	};
}
#endif