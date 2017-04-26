#pragma once
#include <vector>

class LuaTable
{
protected:
	LuaTable();
public:

	virtual ~LuaTable();

	virtual const std::vector<std::string>& GetKeys()const = 0;
	virtual LuaTable* GetTable(const char* tableName) = 0;
};

