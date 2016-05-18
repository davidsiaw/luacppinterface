
if COND_GCOV
   MAYBE_COVERAGE=-fprofile-arcs
endif

TESTS = demonstration1 demonstration2 demonstration3 demonstration4 luacpp testcallabletable testchartowideconvert testcoroutineexception testcoroutineexpectedbutnot testcreate testctoluafunction testexceptioninluafunction testextractingasfunctionbutistable testfunction testfunctionerror testfunctionexpectedbutnotcallable testfunctionparams testfunctionparamsreturn testfunctionreturn testgetmetatableonclosedstate testgetsetfunction testgetsetfunction2 testgetsetinsidetable testgetsetinteger testgetsetstring testgetsettable testgetstate testgettypeofvalueat testinvalidscript testpassingfunction testreadinglightuserdatafromuserdata testregistry testresumenoscript testreturnfromnative testreturnfromscript testreturnfromyieldingfunction testreturntablefromlua testreturntablefromnative testscriptexception testsetstring testsetwstring testtable testtableexpectedbutnotable testtableforeachintegerkey testtableforeachstringkey testtypeintstringmorph testtypemorphintwstring testtypestringintmorph testuserdata testuserdataconstructor testuserdatadispose testuserdatamethod testwidetocharconvert

check_PROGRAMS = $(TESTS)
		
AM_CXXFLAGS = -I../LuaCppInterface -I../lua/src $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(MAYBE_COVERAGE)
REQUIRED_LIBS = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

demonstration1_SOURCES = demonstration1.cpp lua
demonstration1_LDADD = $(REQUIRED_LIBS)

demonstration2_SOURCES = demonstration2.cpp lua
demonstration2_LDADD = $(REQUIRED_LIBS)

demonstration3_SOURCES = demonstration3.cpp lua
demonstration3_LDADD = $(REQUIRED_LIBS)

demonstration4_SOURCES = demonstration4.cpp lua
demonstration4_LDADD = $(REQUIRED_LIBS)

luacpp_SOURCES = luacpp.cpp lua
luacpp_LDADD = $(REQUIRED_LIBS)

testcallabletable_SOURCES = testcallabletable.cpp lua
testcallabletable_LDADD = $(REQUIRED_LIBS)

testchartowideconvert_SOURCES = testchartowideconvert.cpp lua
testchartowideconvert_LDADD = $(REQUIRED_LIBS)

testcoroutineexception_SOURCES = testcoroutineexception.cpp lua
testcoroutineexception_LDADD = $(REQUIRED_LIBS)

testcoroutineexpectedbutnot_SOURCES = testcoroutineexpectedbutnot.cpp lua
testcoroutineexpectedbutnot_LDADD = $(REQUIRED_LIBS)

testcreate_SOURCES = testcreate.cpp lua
testcreate_LDADD = $(REQUIRED_LIBS)

testctoluafunction_SOURCES = testctoluafunction.cpp lua
testctoluafunction_LDADD = $(REQUIRED_LIBS)

testexceptioninluafunction_SOURCES = testexceptioninluafunction.cpp lua
testexceptioninluafunction_LDADD = $(REQUIRED_LIBS)

testextractingasfunctionbutistable_SOURCES = testextractingasfunctionbutistable.cpp lua
testextractingasfunctionbutistable_LDADD = $(REQUIRED_LIBS)

testfunction_SOURCES = testfunction.cpp lua
testfunction_LDADD = $(REQUIRED_LIBS)

testfunctionerror_SOURCES = testfunctionerror.cpp lua
testfunctionerror_LDADD = $(REQUIRED_LIBS)

testfunctionexpectedbutnotcallable_SOURCES = testfunctionexpectedbutnotcallable.cpp lua
testfunctionexpectedbutnotcallable_LDADD = $(REQUIRED_LIBS)

testfunctionparams_SOURCES = testfunctionparams.cpp lua
testfunctionparams_LDADD = $(REQUIRED_LIBS)

testfunctionparamsreturn_SOURCES = testfunctionparamsreturn.cpp lua
testfunctionparamsreturn_LDADD = $(REQUIRED_LIBS)

testfunctionreturn_SOURCES = testfunctionreturn.cpp lua
testfunctionreturn_LDADD = $(REQUIRED_LIBS)

testgetmetatableonclosedstate_SOURCES = testgetmetatableonclosedstate.cpp lua
testgetmetatableonclosedstate_LDADD = $(REQUIRED_LIBS)

testgetsetfunction_SOURCES = testgetsetfunction.cpp lua
testgetsetfunction_LDADD = $(REQUIRED_LIBS)

testgetsetfunction2_SOURCES = testgetsetfunction2.cpp lua
testgetsetfunction2_LDADD = $(REQUIRED_LIBS)

testgetsetinsidetable_SOURCES = testgetsetinsidetable.cpp lua
testgetsetinsidetable_LDADD = $(REQUIRED_LIBS)

testgetsetinteger_SOURCES = testgetsetinteger.cpp lua
testgetsetinteger_LDADD = $(REQUIRED_LIBS)

testgetsetstring_SOURCES = testgetsetstring.cpp lua
testgetsetstring_LDADD = $(REQUIRED_LIBS)

testgetsettable_SOURCES = testgetsettable.cpp lua
testgetsettable_LDADD = $(REQUIRED_LIBS)

testgetstate_SOURCES = testgetstate.cpp lua
testgetstate_LDADD = $(REQUIRED_LIBS)

testgettypeofvalueat_SOURCES = testgettypeofvalueat.cpp lua
testgettypeofvalueat_LDADD = $(REQUIRED_LIBS)

testinvalidscript_SOURCES = testinvalidscript.cpp lua
testinvalidscript_LDADD = $(REQUIRED_LIBS)

testpassingfunction_SOURCES = testpassingfunction.cpp lua
testpassingfunction_LDADD = $(REQUIRED_LIBS)

testreadinglightuserdatafromuserdata_SOURCES = testreadinglightuserdatafromuserdata.cpp lua
testreadinglightuserdatafromuserdata_LDADD = $(REQUIRED_LIBS)

testregistry_SOURCES = testregistry.cpp lua
testregistry_LDADD = $(REQUIRED_LIBS)

testresumenoscript_SOURCES = testresumenoscript.cpp lua
testresumenoscript_LDADD = $(REQUIRED_LIBS)

testreturnfromnative_SOURCES = testreturnfromnative.cpp lua
testreturnfromnative_LDADD = $(REQUIRED_LIBS)

testreturnfromscript_SOURCES = testreturnfromscript.cpp lua
testreturnfromscript_LDADD = $(REQUIRED_LIBS)

testreturnfromyieldingfunction_SOURCES = testreturnfromyieldingfunction.cpp lua
testreturnfromyieldingfunction_LDADD = $(REQUIRED_LIBS)

testreturntablefromlua_SOURCES = testreturntablefromlua.cpp lua
testreturntablefromlua_LDADD = $(REQUIRED_LIBS)

testreturntablefromnative_SOURCES = testreturntablefromnative.cpp lua
testreturntablefromnative_LDADD = $(REQUIRED_LIBS)

testscriptexception_SOURCES = testscriptexception.cpp lua
testscriptexception_LDADD = $(REQUIRED_LIBS)

testsetstring_SOURCES = testsetstring.cpp lua
testsetstring_LDADD = $(REQUIRED_LIBS)

testsetwstring_SOURCES = testsetwstring.cpp lua
testsetwstring_LDADD = $(REQUIRED_LIBS)

testtable_SOURCES = testtable.cpp lua
testtable_LDADD = $(REQUIRED_LIBS)

testtableexpectedbutnotable_SOURCES = testtableexpectedbutnotable.cpp lua
testtableexpectedbutnotable_LDADD = $(REQUIRED_LIBS)

testtableforeachintegerkey_SOURCES = testtableforeachintegerkey.cpp lua
testtableforeachintegerkey_LDADD = $(REQUIRED_LIBS)

testtableforeachstringkey_SOURCES = testtableforeachstringkey.cpp lua
testtableforeachstringkey_LDADD = $(REQUIRED_LIBS)

testtypeintstringmorph_SOURCES = testtypeintstringmorph.cpp lua
testtypeintstringmorph_LDADD = $(REQUIRED_LIBS)

testtypemorphintwstring_SOURCES = testtypemorphintwstring.cpp lua
testtypemorphintwstring_LDADD = $(REQUIRED_LIBS)

testtypestringintmorph_SOURCES = testtypestringintmorph.cpp lua
testtypestringintmorph_LDADD = $(REQUIRED_LIBS)

testuserdata_SOURCES = testuserdata.cpp lua
testuserdata_LDADD = $(REQUIRED_LIBS)

testuserdataconstructor_SOURCES = testuserdataconstructor.cpp lua
testuserdataconstructor_LDADD = $(REQUIRED_LIBS)

testuserdatadispose_SOURCES = testuserdatadispose.cpp lua
testuserdatadispose_LDADD = $(REQUIRED_LIBS)

testuserdatamethod_SOURCES = testuserdatamethod.cpp lua
testuserdatamethod_LDADD = $(REQUIRED_LIBS)

testwidetocharconvert_SOURCES = testwidetocharconvert.cpp lua
testwidetocharconvert_LDADD = $(REQUIRED_LIBS)



BUILT_SOURCES = ../lua/src/liblua.a

CLEANFILES = $(BUILT_SOURCES)

../lua/src/liblua.a:
	cd ../lua && make generic
	
clean-local:
	cd ../lua && make clean


