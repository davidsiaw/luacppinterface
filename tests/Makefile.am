
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
		testchartowideconvert \
		testwidetocharconvert \
		teststricttypingerror \
		teststricttyping \
		demonstration1 \
		demonstration2 \
		demonstration3 \
		demonstration4

check_PROGRAMS = $(TESTS)
		
AM_CXXFLAGS = -I../LuaCppInterface -I../lua/src $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(MAYBE_COVERAGE) -L../LuaCppInterface -L../lua/src -llua -lluacppinterface

crashtest_SOURCES = luacpp.cpp lua

testcreate_SOURCES = testcreate.cpp lua

testfunction_SOURCES = testfunction.cpp lua

testfunctionparams_SOURCES = testfunctionparams.cpp lua

testfunctionparamsreturn_SOURCES = testfunctionparamsreturn.cpp lua

testfunctionreturn_SOURCES = testfunctionreturn.cpp lua

testgetsetfunction_SOURCES = testgetsetfunction.cpp lua

testgetsetinsidetable_SOURCES = testgetsetinsidetable.cpp lua

testgetsetinteger_SOURCES = testgetsetinteger.cpp lua

testgetsetstring_SOURCES = testgetsetstring.cpp lua

testgetsettable_SOURCES = testgetsettable.cpp lua

testpassingfunction_SOURCES = testpassingfunction.cpp lua

testreturnfromnative_SOURCES = testreturnfromnative.cpp lua

testreturnfromscript_SOURCES = testreturnfromscript.cpp lua

testreturntablefromlua_SOURCES = testreturntablefromlua.cpp lua

testreturntablefromnative_SOURCES = testreturntablefromnative.cpp lua

testuserdata_SOURCES = testuserdata.cpp lua

testuserdataconstructor_SOURCES = testuserdataconstructor.cpp lua

testuserdatamethod_SOURCES = testuserdatamethod.cpp lua

testuserdatadispose_SOURCES = testuserdatadispose.cpp lua

testtable_SOURCES = testtable.cpp lua


testscriptexception_SOURCES = testscriptexception.cpp lua

testtableforeachintegerkey_SOURCES = testtableforeachintegerkey.cpp lua

testtableforeachstringkey_SOURCES = testtableforeachstringkey.cpp lua

testgettypeofvalueat_SOURCES = testgettypeofvalueat.cpp lua

testinvalidscript_SOURCES = testinvalidscript.cpp lua

testregistry_SOURCES = testregistry.cpp lua

testreturnfromyieldingfunction_SOURCES = testreturnfromyieldingfunction.cpp lua

testchartowideconvert_SOURCES = testchartowideconvert.cpp lua

testwidetocharconvert_SOURCES = testwidetocharconvert.cpp lua


teststricttypingerror_SOURCES = teststricttypingerror.cpp lua

teststricttyping_SOURCES = teststricttyping.cpp lua


demonstration1_SOURCES = demonstration1.cpp lua

demonstration2_SOURCES = demonstration2.cpp lua

demonstration3_SOURCES = demonstration3.cpp lua

demonstration4_SOURCES = demonstration4.cpp lua


BUILT_SOURCES = ../lua/src/liblua.a


CLEANFILES = $(BUILT_SOURCES)

../lua/src/liblua.a:
	cd ../lua && make generic
	
clean-local:
	cd ../lua && make clean
