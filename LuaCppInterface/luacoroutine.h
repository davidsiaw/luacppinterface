#ifndef LUACOROUTINE_H
#define LUACOROUTINE_H

#include <cassert>
#include <string>
#include "luareference.h"

class LuaCoroutine : public LuaReference
{
	int status;

public:
	LuaCoroutine(std::tr1::shared_ptr<lua_State> state, int index);
	std::string RunScript(std::string script);
	std::string Resume();
	bool CanResume() const;
};

#endif // LUACOROUTINE_H
