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

public:
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
