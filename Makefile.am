ACLOCAL_AMFLAGS = -I build-aux
SUBDIRS = LuaCppInterface

TESTS = luainterfacetest testcreate testtable testgetsetinsidetable demonstration1 demonstration2 demonstration3

check_PROGRAMS = luainterfacetest testcreate testtable testgetsetinsidetable demonstration1 demonstration2 demonstration3
AM_CXXFLAGS = -ILuaCppInterface -Ilua/src $(BOOST_CPPFLAGS)

luainterfacetest_SOURCES = LuaCppTest/luacpp.cpp lua
luainterfacetest_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testcreate_SOURCES = tests/testcreate.cpp lua
testcreate_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testtable_SOURCES = tests/testtable.cpp lua
testtable_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testgetsetinsidetable_SOURCES = tests/testgetsetinsidetable.cpp lua
testgetsetinsidetable_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a


demonstration1_SOURCES = tests/demonstration1.cpp lua
demonstration1_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

demonstration2_SOURCES = tests/demonstration2.cpp lua
demonstration2_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

demonstration3_SOURCES = tests/demonstration3.cpp lua
demonstration3_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

BUILT_SOURCES = lua/src/liblua.a

CLEANFILES = $(BUILT_SOURCES)

lua/src/liblua.a:
	cd lua && make generic
	
clean-local:
	cd lua && make clean