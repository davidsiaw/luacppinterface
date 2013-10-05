#ifndef LUAUSERDATA_H
#define LUAUSERDATA_H

#include <cassert>
#include "luatype.h"
#include "luareference.h"

template<typename TYPE>
class LuaUserdata : public LuaReference
{
public:
	LuaUserdata(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
	{
		assert(GetType() == LuaType::userdata);
	}
	
	template<typename OBJ>
	void Set(std::string key, const OBJ& value)
	{
		auto table = GetMetaTable();
		table.Set<OBJ>(key, value);
	}
	
	template<typename OBJ>
	OBJ Get(std::string key) const
	{
		auto table = GetMetaTable();
		return table.Get<OBJ>(key);
	}
};


#endif // LUAUSERDATA_H
