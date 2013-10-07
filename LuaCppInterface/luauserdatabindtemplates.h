
	template<typename TYPE>
	template<typename RET>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)() )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET()>(std::tr1::bind(func, t));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
	
	template<typename TYPE>
	template<typename RET, typename ARG0>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0) )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0)>(std::tr1::bind(func, t, _1));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
	
	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1) )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1)>(std::tr1::bind(func, t, _1, _2));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
	
	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2)>(std::tr1::bind(func, t, _1, _2, _3));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
	
	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3)>(std::tr1::bind(func, t, _1, _2, _3, _4));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
	
	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4)>(std::tr1::bind(func, t, _1, _2, _3, _4, _5));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
	
	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5)>(std::tr1::bind(func, t, _1, _2, _3, _4, _5, _6));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
	
	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6)>(std::tr1::bind(func, t, _1, _2, _3, _4, _5, _6, _7));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
	
	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) )
	{
		using namespace std::tr1::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7)>(std::tr1::bind(func, t, _1, _2, _3, _4, _5, _6, _7, _8));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
