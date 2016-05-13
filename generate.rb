items = Dir["tests/*.cpp"].map {|x| File.basename(x, ".cpp")}

rule_sets = items.map do |x|
	<<-RULE
#{x}_SOURCES = #{x}.cpp lua
#{x}_LDADD = $(REQUIRED_LIBS)

	RULE
end.join ""

rule_list = items.map { |x| "#{x}" }.join " "

makefile_am = <<-MAKEFILE_AM

if COND_GCOV
   MAYBE_COVERAGE=-fprofile-arcs
endif

TESTS = #{rule_list}

check_PROGRAMS = $(TESTS)
		
AM_CXXFLAGS = -I../LuaCppInterface -I../lua/src $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(MAYBE_COVERAGE)
REQUIRED_LIBS = ../LuaCppInterface/libluacppinterface.a ../lua/src/liblua.a

#{rule_sets}

BUILT_SOURCES = ../lua/src/liblua.a

CLEANFILES = $(BUILT_SOURCES)

../lua/src/liblua.a:
	cd ../lua && make generic
	
clean-local:
	cd ../lua && make clean


MAKEFILE_AM

File.write("tests/Makefile.am", makefile_am)