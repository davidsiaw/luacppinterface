
	template<typename RET>
	void Bind(std::string name, RET(TYPE::*func)() );

	template<typename RET, typename ARG0>
	void Bind(std::string name, RET(TYPE::*func)(ARG0) );

	template<typename RET, typename ARG0, typename ARG1>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1) );
	
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) );
	
	template<typename RET>
	void BindYield(std::string name, RET(TYPE::*func)() );

	template<typename RET, typename ARG0>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0) );

	template<typename RET, typename ARG0, typename ARG1>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1) );
	
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) );

	template<typename RET>
	void Bind(std::string name, RET(TYPE::*func)() const );

	template<typename RET, typename ARG0>
	void Bind(std::string name, RET(TYPE::*func)(ARG0) const );

	template<typename RET, typename ARG0, typename ARG1>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1) const );
	
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void Bind(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) const );
	
	template<typename RET>
	void BindYield(std::string name, RET(TYPE::*func)() const );

	template<typename RET, typename ARG0>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0) const );

	template<typename RET, typename ARG0, typename ARG1>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1) const );
	
	template<typename RET, typename ARG0, typename ARG1, typename ARG2>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const );

	template<typename RET, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6, typename ARG7>
	void BindYield(std::string name, RET(TYPE::*func)(ARG0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) const );
	