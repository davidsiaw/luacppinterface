#ifndef LUALIGHTUSERDATA_H
#define LUALIGHTUSERDATA_H

#include <cassert>
#include <memory>
#include "luareference.h"
#include "luatype.h"
#include "luauserdata.h"

template <typename T>
class LuaLightUserdata : public LuaReference
{
	T* pointer;

public:
	LuaLightUserdata(std::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
	{
		assert(GetType() == LuaType::userdata || GetType() == LuaType::lightuserdata);

		if (GetType() == LuaType::lightuserdata)
		{
			pointer = (T*)lua_touserdata(state.get(), index);
		}
		else if (GetType() == LuaType::userdata)
		{
			auto wrap = (typename LuaUserdata<T>::UserdataWrapper*)lua_touserdata(state.get(), index);
			pointer = wrap->actualData;
		}
		else
		{
			const char *msg = lua_pushfstring(state.get(), "userdata or lightuserdata expected, got %s", luaL_typename(state.get(), index));
			luaL_argerror(state.get(), index, msg);
		}
	}

	T* GetPointer() const
	{
		return pointer;
	}

    T* operator->() const { return pointer; }
};


#endif // LUALIGHTUSERDATA_H
