ACLOCAL_AMFLAGS = -I build-aux
SUBDIRS = LuaCppInterface

TESTS = luainterfacetest \
		testcreate \
		testfunction \
		testfunctionparams \
		testfunctionparamsreturn \
		testfunctionreturn \
		testgetsetfunction \
		testgetsetinsidetable \
		testgetsetinteger \
		testgetsetstring \
		testgetsettable \
		testpassingfunction \
		testreturnfromnative \
		testreturnfromscript \
		testreturntablefromlua \
		testreturntablefromnative \
		testtable \
		demonstration1 \
		demonstration2 \
		demonstration3

check_PROGRAMS = luainterfacetest \
		testcreate \
		testfunction \
		testfunctionparams \
		testfunctionparamsreturn \
		testfunctionreturn \
		testgetsetfunction \
		testgetsetinsidetable \
		testgetsetinteger \
		testgetsetstring \
		testgetsettable \
		testpassingfunction \
		testreturnfromnative \
		testreturnfromscript \
		testreturntablefromlua \
		testreturntablefromnative \
		testtable \
		demonstration1 \
		demonstration2 \
		demonstration3
		
AM_CXXFLAGS = -ILuaCppInterface -Ilua/src $(BOOST_CPPFLAGS)

luainterfacetest_SOURCES = LuaCppTest/luacpp.cpp lua
luainterfacetest_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a


testcreate_SOURCES = tests/testcreate.cpp lua
testcreate_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testfunction_SOURCES = tests/testfunction.cpp lua
testfunction_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testfunctionparams_SOURCES = tests/testfunctionparams.cpp lua
testfunctionparams_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testfunctionparamsreturn_SOURCES = tests/testfunctionparamsreturn.cpp lua
testfunctionparamsreturn_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testfunctionreturn_SOURCES = tests/testfunctionreturn.cpp lua
testfunctionreturn_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testgetsetfunction_SOURCES = tests/testgetsetfunction.cpp lua
testgetsetfunction_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testgetsetinsidetable_SOURCES = tests/testgetsetinsidetable.cpp lua
testgetsetinsidetable_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testgetsetinteger_SOURCES = tests/testgetsetinteger.cpp lua
testgetsetinteger_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testgetsetstring_SOURCES = tests/testgetsetstring.cpp lua
testgetsetstring_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testgetsettable_SOURCES = tests/testgetsettable.cpp lua
testgetsettable_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testpassingfunction_SOURCES = tests/testpassingfunction.cpp lua
testpassingfunction_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testreturnfromnative_SOURCES = tests/testreturnfromnative.cpp lua
testreturnfromnative_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testreturnfromscript_SOURCES = tests/testreturnfromscript.cpp lua
testreturnfromscript_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testreturntablefromlua_SOURCES = tests/testreturntablefromlua.cpp lua
testreturntablefromlua_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testreturntablefromnative_SOURCES = tests/testreturntablefromnative.cpp lua
testreturntablefromnative_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

testtable_SOURCES = tests/testtable.cpp lua
testtable_LDADD = LuaCppInterface/libluacppinterface.a lua/src/liblua.a

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