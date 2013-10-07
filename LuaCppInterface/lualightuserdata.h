#ifndef LUALIGHTUSERDATA_H
#define LUALIGHTUSERDATA_H

#include <cassert>
#include <boost/tr1/memory.hpp>
#include "luareference.h"
#include "luatype.h"

template <typename T>
class LuaLightUserdata : public LuaReference
{
	T* pointer;

public:
	LuaLightUserdata(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
	{
		assert(GetType() == LuaType::userdata || GetType() == LuaType::lightuserdata);

		if (GetType() == LuaType::lightuserdata)
		{
			pointer = (T*)lua_touserdata(state.get(), index);
		}
		else if (GetType() == LuaType::userdata)
		{
			auto wrap = (LuaUserdata<T>::UserdataWrapper*)lua_touserdata(state.get(), index);
			pointer = wrap->actualData;
		}
	}

	T* GetPointer() const
	{
		return pointer;
	}
};


#endif // LUALIGHTUSERDATA_H