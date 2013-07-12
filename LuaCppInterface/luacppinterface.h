#ifndef LUACPPINTERFACE_H
#define LUACPPINTERFACE_H

#include <memory>
#include <functional>
#include "luatable.h"
#include "luafunction.h"

class Lua
{
	std::tr1::shared_ptr<lua_State> state;
	LuaTable registry;
	LuaTable globals;

public:
	Lua();
	~Lua();

	LuaTable GetRegistry();
	LuaTable GetGlobalEnvironment();
	LuaTable CreateTable();
	static int staticFunction(lua_State* state);
	LuaFunction CreateFunction(const std::tr1::function<LuaTable(LuaTable)>* func);
	std::string RunScript(std::string script);

};

#endif // LUACPPINTERFACE
