#ifndef LUAUSERDATA_H
#define LUAUSERDATA_H

#include <cassert>
#include <boost/tr1/functional.hpp>
#include "luatype.h"
#include "luareference.h"

class Lua;
class LuaTable;

template<typename TYPE>
class LuaUserdata : public LuaReference
{
	TYPE* pointer;

public:
	LuaUserdata(std::tr1::shared_ptr<lua_State> state, int index) : 
	  LuaReference(state, index)
	{
		assert(GetType() == LuaType::userdata);
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

#include "luauserdataforwards.h"
	
	struct UserdataWrapper
	{
		TYPE* actualData;
		std::tr1::function< void(TYPE*) > destructor;
	};

	static int lua_userdata_finalizer(lua_State* state)
	{
		UserdataWrapper* wrap = (UserdataWrapper*)lua_touserdata(state, lua_upvalueindex(1));
		wrap->destructor(wrap->actualData);
		return 0;
	};
	
	TYPE* RetrieveData() const
	{
		PushToStack();
		UserdataWrapper* wrap = (UserdataWrapper*)lua_touserdata(state.get(), -1);
		lua_pop(state.get(), 1);
		return wrap->actualData;
	}	
};


#endif // LUAUSERDATA_H
