#ifndef LUAGENERICFUNCTION_H
#define LUAGENERICFUNCTION_H

#include <boost/tr1/functional.hpp>
#include "luafunctionbase.h"

template<typename T>
std::tr1::shared_ptr<T> LuaNoDestructor(T* obj)
{
	return std::tr1::shared_ptr<T>(obj, [](T*){});
}

#include "luageneralgenericfunctions.h"
#include "luavoidgenericfunctions.h"

#endif // LUAGENERICFUNCTION_H
