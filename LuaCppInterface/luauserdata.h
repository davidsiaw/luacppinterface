#ifndef LUAUSERDATA_H
#define LUAUSERDATA_H

#include <cassert>
#include <functional>
#include "luatype.h"
#include "luareference.h"

class Lua;
class LuaTable;

template<typename TYPE>
class LuaUserdata : public LuaReference
{
	TYPE* pointer;

	int pushUserdata(std::shared_ptr<lua_State> state, TYPE* data, std::function<void(TYPE*)> destructor)
	{
		UserdataWrapper* wrap = (UserdataWrapper*)lua_newuserdata(state.get(), sizeof(UserdataWrapper));
        
		memset(wrap, 0, sizeof(typename LuaUserdata<TYPE>::UserdataWrapper));
        
		wrap->actualData = data;
		wrap->destructor = new std::function<void(TYPE*)> (destructor);

		return -1;
	}

public:
	LuaUserdata(std::shared_ptr<lua_State> state, TYPE* data) : LuaUserdata(state, data, [](TYPE* data){ delete data; })
	{ }
	
	LuaUserdata(std::shared_ptr<lua_State> state, TYPE* data, std::function<void(TYPE*)> destructor) : LuaUserdata(state, pushUserdata(state, data, destructor))
	{
		// The wrapper pointer is on the top of the stack
		UserdataWrapper* wrap = (UserdataWrapper*)lua_touserdata(state.get(), -1);

		lua_newtable(state.get());

		// make the finalizer
		lua_pushstring(state.get(), "__gc");
		lua_pushlightuserdata(state.get(), (void*)wrap);
		lua_pushcclosure(state.get(), lua_userdata_finalizer, 1);
		lua_rawset(state.get(), -3);

		// assign table to self
		lua_pushstring(state.get(), "__index");
		lua_pushvalue(state.get(), -2);
		lua_rawset(state.get(), -3);

		lua_setmetatable(state.get(), -2);

		lua_pop(state.get(), 1);
	}

	LuaUserdata(std::shared_ptr<lua_State> state, int index) :
	  LuaReference(state, index)
	{
		assert(GetType() == LuaType::userdata);

		if (GetType() != LuaType::userdata)
		{
			const char *msg = lua_pushfstring(state.get(), "userdata expected, got %s", luaL_typename(state.get(), index));
			luaL_argerror(state.get(), index, msg);
		}

		assert(typeid(TYPE*) == typeid(RetrieveData()));

		auto wrap = (UserdataWrapper*)lua_touserdata(state.get(), index);
		pointer = wrap->actualData;
	}

	template<typename OBJ>
	void Set(std::string key, const OBJ& value)
	{
		LuaTable table = GetMetaTable();
		table.template Set<OBJ>(key, value);
	}

	template<typename OBJ>
	OBJ Get(std::string key) const
	{
		LuaTable table = GetMetaTable();
		return table.template Get<OBJ>(key);
	}

	TYPE* GetPointer() const
	{
		return pointer;
	}
	
    TYPE* operator->() const { return pointer; }

#include "luauserdataforwards.h"

	struct UserdataWrapper
	{
		TYPE* actualData;
		std::function< void(TYPE*) >* destructor;
	};

	static int lua_userdata_finalizer(lua_State* state)
	{
		UserdataWrapper* wrap = (UserdataWrapper*)lua_touserdata(state, lua_upvalueindex(1));
		(*wrap->destructor)(wrap->actualData);
        delete(wrap->destructor);
		return 0;
	};

	TYPE* RetrieveData() const
	{
		PushToStack(state.get());
		UserdataWrapper* wrap = (UserdataWrapper*)lua_touserdata(state.get(), -1);
		lua_pop(state.get(), 1);
		return wrap->actualData;
	}

};


#endif // LUAUSERDATA_H
