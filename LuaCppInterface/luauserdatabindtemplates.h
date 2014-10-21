
	template<typename TYPE>
	template<typename RET>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)() )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET()>(std::bind(func, t));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0)>(std::bind(func, t, std::placeholders::_1));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)() )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET()>(std::bind(func, t));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0)>(std::bind(func, t, std::placeholders::_1));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}


	template<typename TYPE>
	template<typename RET>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)() const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET()>(std::bind(func, t));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0)>(std::bind(func, t, std::placeholders::_1));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void LuaUserdata<TYPE>::Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)() const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET()>(std::bind(func, t));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0)>(std::bind(func, t, std::placeholders::_1));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}

	template<typename TYPE>
	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void LuaUserdata<TYPE>::BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) const )
	{
		using namespace std::placeholders;
		TYPE* t = RetrieveData();
		Lua lua(state);
		auto luaFunc = lua.CreateYieldingFunction<RET(ARG0,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7)>(std::bind(func, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8));
		LuaTable table = GetMetaTable();
		table.Set(name, luaFunc);
	}
