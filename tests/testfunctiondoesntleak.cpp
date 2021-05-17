// Test for CreateFunction memory leak

#include <memory>
#include <luacppinterface.h>

struct Functor {
	std::shared_ptr<int> ptr;

	void operator()() const {
		// no-op
	}
};

int main()
{
	Lua lua;

	// Create a LuaFunction from a functor that holds a shared_ptr to
	// a resource. If the function created via CreateFunction gets
	// collected by the GC, the weak pointer will expire after that
	std::weak_ptr<int> weak;
	{
		auto ptr = std::make_shared<int>(0);
		weak = ptr;
		auto function = lua.CreateFunction<void()>(Functor{ptr});
	}

	lua.CollectGarbage();

	return !weak.expired();
}
