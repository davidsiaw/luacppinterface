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

include_list = {}

test_sections = ""

test_items = items.map do |item|

	include_regex = /^\#include <[a-zA-Z0-9.]+>\s*/
	file_content = File.read("tests/#{item}.cpp")

	file_content.scan(include_regex) {|x| include_list[x.to_s] = true }

	contents = file_content
	contents.gsub!(include_regex, "")
	contents.gsub!(/^/, "\t")

	test_sections += <<-TEST_SECTION

namespace section_#{item}
{
#{contents}
}
	TEST_SECTION

	<<-TEST_CONTENT

		TEST_METHOD(#{item})
		{
			Assert::IsTrue(section_#{item}::main() == 0);
		}
	TEST_CONTENT
end.join ""

msvc_test = <<-MSVC_TEST
#include "stdafx.h"
#include "CppUnitTest.h"

#define FAIL_IF(x) return Assert::IsFalse(x);

// ============================================================================
// WARNING: THIS FILE IS GENERATED FROM THE TEST SOURCES IN THE tests FOLDER. 
// Run generate.rb to update
// ============================================================================

#{include_list.keys.join("\r\n")}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#{test_sections}

namespace LuaCppInterfaceTests
{		
	TEST_CLASS(UnitTests)
	{
	public:
#{test_items}
	};
}
MSVC_TEST

File.write("LuaCppInterfaceTests/unittest1.cpp", msvc_test)