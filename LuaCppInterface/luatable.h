#ifndef LUATABLE_H
#define LUATABLE_H

#include <cassert>
#include <string>
#include <memory>
#include "luareference.h"
#include "luafunction.h"

class LuaTable : public LuaReference
{

public:
	LuaTable(std::tr1::shared_ptr<lua_State> state, int index);

	void SetTable(std::string key, const LuaTable& value);	
	void SetTable(int key, const LuaTable& value);
	void SetInteger(std::string key, const int value);
	void SetInteger(int key, const int value);	
	void SetString(std::string key, const std::string value);
	void SetString(int key, const std::string value);	
	void SetFunction(std::string key, const LuaFunction value);
	void SetFunction(int key, const LuaFunction value);

	LuaTable GetTable(std::string key) const;
	LuaTable GetTable(int key) const;	
	int GetInteger(std::string key) const;
	int GetInteger(int key) const;
	std::string GetString(std::string key) const;
	std::string GetString(int key) const;	
	LuaFunction GetFunction(std::string key) const;
	LuaFunction GetFunction(int key) const;
};

#endif // LUATABLE_H
