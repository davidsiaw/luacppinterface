#ifndef LUACOROUTINE_H
#define LUACOROUTINE_H

#include <cassert>
#include <string>
#include "luareference.h"

class LuaCoroutine : public LuaReference
{
public:
	LuaCoroutine(std::shared_ptr<lua_State> state, int index);

	// run a script
	std::string RunScript(std::string script);

	// resume the yielded coroutine
	std::string Resume();

	bool CanResume() const;
};

#endif // LUACOROUTINE_H
