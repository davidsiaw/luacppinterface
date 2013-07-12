#include <iostream>

#include <lua.hpp>

#include <string>
#include <functional>
#include <memory>
#include <cassert>

namespace LuaType
{
	enum Value
	{
		none = LUA_TNONE,
		nil = LUA_TNIL,
		string = LUA_TSTRING,
		number = LUA_TNUMBER,
		thread = LUA_TTHREAD,
		boolean = LUA_TBOOLEAN,
		function = LUA_TFUNCTION,
		userdata = LUA_TUSERDATA,
		lightuserdata = LUA_TLIGHTUSERDATA,
		table = LUA_TTABLE
	};
}

class LuaTable;
class LuaReference
{
	int ref;

protected:
	std::tr1::shared_ptr<lua_State> state;

public:
	LuaReference(std::tr1::shared_ptr<lua_State> state, int index) : state(state)
	{
		lua_pushvalue(state.get(), index);
		ref = luaL_ref(state.get(), LUA_REGISTRYINDEX);;
	}

	LuaReference(const LuaReference& other)
	{
		*this = other;
	}

	LuaReference& operator=(const LuaReference& other)
	{ 
		state = other.state;
		other.PushToStack();
		ref = luaL_ref(state.get(), LUA_REGISTRYINDEX);
		return *this;
	}
	
	virtual ~LuaReference()
	{
		luaL_unref(state.get(), LUA_REGISTRYINDEX, ref);
	}

	void PushToStack() const
	{
		lua_rawgeti(state.get(), LUA_REGISTRYINDEX, ref);
	}

	LuaType::Value GetType() const
	{
		PushToStack();
		LuaType::Value val = (LuaType::Value)lua_type(state.get(), -1);
		lua_pop(state.get(), 1);
		return val;
	}

	std::tr1::shared_ptr<lua_State> GetState()
	{
		return state;
	}

	LuaTable GetMetaTable() const;
};

class LuaFunction : public LuaReference
{
public:
	LuaFunction(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
	{
		auto a = GetType();
		assert(GetType() == LuaType::function);
	}

	LuaTable Invoke(LuaTable table);
};

class LuaTable : public LuaReference
{

public:
	LuaTable(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
	{
		assert(GetType() == LuaType::table);
	}

	void SetTable(std::string key, const LuaTable& value)
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		value.PushToStack();
		lua_settable(state.get(), -3);
		lua_pop(state.get(), 1);
	}
	
	void SetTable(int key, const LuaTable& value)
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		value.PushToStack();
		lua_settable(state.get(), -3);
		lua_pop(state.get(), 1);
	}

	void SetInteger(std::string key, const int value)
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_pushinteger(state.get(), value);
		lua_settable(state.get(), -3);
		lua_pop(state.get(), 1);
	}

	void SetInteger(int key, const int value)
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		lua_pushinteger(state.get(), value);
		lua_settable(state.get(), -3);
		lua_pop(state.get(), 1);
	}
	
	void SetString(std::string key, const std::string value)
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_pushlstring(state.get(), value.c_str(), value.length());
		lua_settable(state.get(), -3);
		lua_pop(state.get(), 1);
	}

	void SetString(int key, const std::string value)
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		lua_pushlstring(state.get(), value.c_str(), value.length());
		lua_settable(state.get(), -3);
		lua_pop(state.get(), 1);
	}
	
	void SetFunction(std::string key, const LuaFunction value)
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		value.PushToStack();
		lua_settable(state.get(), -3);
		lua_pop(state.get(), 1);
	}

	void SetFunction(int key, const LuaFunction value)
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		value.PushToStack();
		lua_settable(state.get(), -3);
		lua_pop(state.get(), 1);
	}

	LuaTable GetTable(std::string key) const
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_gettable(state.get(), -2);

		LuaTable table = LuaTable(state, -1);
		
		lua_pop(state.get(), 2);
		return table;
	}

	LuaTable GetTable(int key) const
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		lua_gettable(state.get(), -2);

		LuaTable table = LuaTable(state, -1);
		
		lua_pop(state.get(), 2);
		return table;
	}
	
	int GetInteger(std::string key) const
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_gettable(state.get(), -2);

		int res = lua_tointeger(state.get(), -1);
		
		lua_pop(state.get(), 2);
		return res;
	}

	int GetInteger(int key) const
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		lua_gettable(state.get(), -2);
		
		int res = lua_tointeger(state.get(), -1);
		
		lua_pop(state.get(), 2);
		return res;
	}

	std::string GetString(std::string key) const
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_gettable(state.get(), -2);

		std::string res = std::string(lua_tostring(state.get(), -1));
		
		lua_pop(state.get(), 2);
		return res;
	}

	std::string GetString(int key) const
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		lua_gettable(state.get(), -2);
		
		std::string res = std::string(lua_tostring(state.get(), -1));
		
		lua_pop(state.get(), 2);
		return res;
	}
	
	LuaFunction GetFunction(std::string key) const
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_gettable(state.get(), -2);

		LuaFunction res = LuaFunction(state, -1);
		
		lua_pop(state.get(), 2);
		return res;
	}

	LuaFunction GetFunction(int key) const
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		lua_gettable(state.get(), -2);
		
		LuaFunction res = LuaFunction(state, -1);
		
		lua_pop(state.get(), 2);
		return res;
	}
};

LuaTable LuaFunction::Invoke(LuaTable args)
{
	PushToStack();
	args.PushToStack();
	lua_call(state.get(), 1, 1);
	LuaTable table = LuaTable(state, -1);
	lua_pop(state.get(), 1);

	return table;
}

LuaTable LuaReference::GetMetaTable() const
{
	PushToStack();
	int res = lua_getmetatable(state.get(), -1);
	assert(res != 0);
	LuaTable table = LuaTable(state, -1);
	lua_pop(state.get(), 2);
	return table;
}

class Lua
{
	std::tr1::shared_ptr<lua_State> state;
	LuaTable registry;
	LuaTable globals;

public:
	Lua() : 
		state(luaL_newstate(), lua_close),
		registry(LuaTable(state, LUA_REGISTRYINDEX)),
		globals(registry.GetTable(LUA_RIDX_GLOBALS))
	{
	}

	LuaTable GetRegistry()
	{
		return registry;
	}

	LuaTable GetGlobalEnvironment()
	{
		return globals;
	}

	LuaTable CreateTable()
	{
		lua_newtable(state.get());
		LuaTable table = LuaTable(state, -1);
		lua_pop(state.get(), 1);
		return table;
	}

	static int staticFunction(lua_State* state)
	{
		std::tr1::function<LuaTable(LuaTable)>* func = (std::tr1::function<LuaTable(LuaTable)>*)lua_touserdata(state, lua_upvalueindex(1));
		LuaTable table(std::tr1::shared_ptr<lua_State>(state, [&](lua_State*){}), -1);
		func->operator()(table);
		return 0;
	}

	struct closure
	{
		std::tr1::function<LuaTable(void*, LuaTable)> func;
		void* object;
		std::tr1::function<void(void*)> cleanup;
	};

	LuaFunction CreateFunction(const std::tr1::function<LuaTable(LuaTable)>* func)
	{
		lua_pushlightuserdata(state.get(), (void*)func);
		lua_pushcclosure(state.get(), staticFunction, 1);
		LuaFunction function = LuaFunction(state, -1);
		lua_pop(state.get(), 1);
		return function;
	}

	void RunScript(std::string script)
	{
		int err = luaL_dostring(state.get(), script.c_str());
		if (err != LUA_OK)
		{
			const char* r = lua_tostring(state.get(), -1);
			std::cout << r << std::endl;
		}
	}

	~Lua()
	{
	}
};

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	auto params = lua.CreateTable();
	params.SetInteger("big", 10);

	auto thefunc = new std::tr1::function<LuaTable(LuaTable)>([&](LuaTable table) -> LuaTable
	{ 
		std::cout << "momo" << std::endl;
		return table;
	});

	auto frunc = lua.CreateFunction(thefunc);
	global.SetFunction("thefunc", frunc);

	lua.RunScript(
		"thefunc({})\n"
		""
		"function meow (a) \n"
		"  a.big = a.big + 5\n"
		"  return a\n"
		"end\n"

		""
		);
	
	auto meow = global.GetFunction("meow");

	auto result = meow.Invoke(params);
	int big = result.GetInteger("big");

	return 0;
}