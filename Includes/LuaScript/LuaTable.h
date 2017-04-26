#pragma once
#include <vector>
namespace MPE
{
	//! A pure virtual class, so we can avoid including the base lua and luabridge src into the whole thing.
	/*!
	This class hides the actual lua and luabridge implementation found in LuaTable_Back
	\sa LuaTable_Back
	*/
	class LuaTable
	{
	protected:
		LuaTable();
	public:

		virtual ~LuaTable();

		virtual const std::vector<std::string>& GetKeys()const = 0;
		virtual LuaTable* GetTable(const char* tableName) = 0;
	};

}