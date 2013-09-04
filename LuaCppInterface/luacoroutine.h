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

	// run a script
	std::string RunScript(std::string script);

	// resume the yielded coroutine
	std::string Resume();

	// check if the coroutine was yielded
	bool CanResume() const;
};

#endif // LUACOROUTINE_H
