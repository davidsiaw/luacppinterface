ACLOCAL_AMFLAGS = -I build-aux
SUBDIRS = LuaCppInterface

TESTS = luainterfacetest

check_PROGRAMS = luainterfacetest
AM_CXXFLAGS = -ILuaCppInterface -Ilua/src $(BOOST_CPPFLAGS)

luainterfacetest_SOURCES = LuaCppTest/luacpp.cpp lua
luainterfacetest_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a
BUILT_SOURCES = lua/src/liblua.a

lua/src/liblua.a:
	cd lua && make generic