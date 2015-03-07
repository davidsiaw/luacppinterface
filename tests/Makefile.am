
if COND_GCOV
   MAYBE_COVERAGE=-fprofile-arcs
endif

TESTS = crashtest \
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
		testuserdata \
		testuserdataconstructor \
		testuserdatamethod \
		testuserdatadispose \
		testtable \
		testscriptexception \
		testtableforeachintegerkey \
		testtableforeachstringkey \
		testgettypeofvalueat \
		testinvalidscript \
		testregistry \
		testreturnfromyieldingfunction \
		demonstration1 \
		demonstration2 \
		demonstration3 \
		demonstration4

check_PROGRAMS = $(TESTS)
		
AM_CXXFLAGS = -I../LuaCppInterface -I../lua/src $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(MAYBE_COVERAGE)

crashtest_SOURCES = luacpp.cpp lua
crashtest_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a


testcreate_SOURCES = testcreate.cpp lua
testcreate_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testfunction_SOURCES = testfunction.cpp lua
testfunction_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testfunctionparams_SOURCES = testfunctionparams.cpp lua
testfunctionparams_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testfunctionparamsreturn_SOURCES = testfunctionparamsreturn.cpp lua
testfunctionparamsreturn_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testfunctionreturn_SOURCES = testfunctionreturn.cpp lua
testfunctionreturn_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testgetsetfunction_SOURCES = testgetsetfunction.cpp lua
testgetsetfunction_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testgetsetinsidetable_SOURCES = testgetsetinsidetable.cpp lua
testgetsetinsidetable_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testgetsetinteger_SOURCES = testgetsetinteger.cpp lua
testgetsetinteger_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testgetsetstring_SOURCES = testgetsetstring.cpp lua
testgetsetstring_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testgetsettable_SOURCES = testgetsettable.cpp lua
testgetsettable_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testpassingfunction_SOURCES = testpassingfunction.cpp lua
testpassingfunction_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testreturnfromnative_SOURCES = testreturnfromnative.cpp lua
testreturnfromnative_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testreturnfromscript_SOURCES = testreturnfromscript.cpp lua
testreturnfromscript_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testreturntablefromlua_SOURCES = testreturntablefromlua.cpp lua
testreturntablefromlua_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testreturntablefromnative_SOURCES = testreturntablefromnative.cpp lua
testreturntablefromnative_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testuserdata_SOURCES = testuserdata.cpp lua
testuserdata_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testuserdataconstructor_SOURCES = testuserdataconstructor.cpp lua
testuserdataconstructor_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testuserdatamethod_SOURCES = testuserdatamethod.cpp lua
testuserdatamethod_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testuserdatadispose_SOURCES = testuserdatadispose.cpp lua
testuserdatadispose_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testtable_SOURCES = testtable.cpp lua
testtable_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a



testscriptexception_SOURCES = testscriptexception.cpp lua
testscriptexception_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testtableforeachintegerkey_SOURCES = testtableforeachintegerkey.cpp lua
testtableforeachintegerkey_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testtableforeachstringkey_SOURCES = testtableforeachstringkey.cpp lua
testtableforeachstringkey_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testgettypeofvalueat_SOURCES = testgettypeofvalueat.cpp lua
testgettypeofvalueat_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testinvalidscript_SOURCES = testinvalidscript.cpp lua
testinvalidscript_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testregistry_SOURCES = testregistry.cpp lua
testregistry_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

testreturnfromyieldingfunction_SOURCES = testreturnfromyieldingfunction.cpp lua
testreturnfromyieldingfunction_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a


demonstration1_SOURCES = demonstration1.cpp lua
demonstration1_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

demonstration2_SOURCES = demonstration2.cpp lua
demonstration2_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

demonstration3_SOURCES = demonstration3.cpp lua
demonstration3_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

demonstration4_SOURCES = demonstration4.cpp lua
demonstration4_LDADD = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a


BUILT_SOURCES = ../lua/src/liblua.a


CLEANFILES = $(BUILT_SOURCES)

../lua/src/liblua.a:
	cd ../lua && make generic
	
clean-local:
	cd ../lua && make clean
