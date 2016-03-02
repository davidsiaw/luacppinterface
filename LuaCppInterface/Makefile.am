if COND_GCOV
   MAYBE_COVERAGE=--coverage
endif

lib_LIBRARIES = libluacppinterface.a
libluacppinterface_a_SOURCES = luacoroutine.cpp luacppinterface.cpp luafunction.cpp luareference.cpp luatable.cpp luaerror.cpp luastringconversion.cpp 
AM_CXXFLAGS = $(MAYBE_COVERAGE) -I../lua/src $(BOOST_CPPFLAGS)
