cmake_minimum_required(VERSION 2.8)

option(test "Build all tests." OFF)

project (snametize CXX)

set (snametize_VERSION_MAJOR 0)
set (snametize VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -g -Wall")

find_package( Boost REQUIRED COMPONENTS program_options)
include_directories( ${Boost_INCLUDE_DIRS} )
add_library(snametize_lib src/snametize.cc src/util/util.cc src/writer/MetisWriter.cc src/writer/GmlWriter.cc src/writer/SnapWriter.cc src/writer/writer.cc)
add_executable(snametize src/main.cc)
target_link_libraries( snametize snametize_lib ${Boost_PROGRAM_OPTIONS_LIBRARY} )

#Testing
if (test)
	add_subdirectory(lib/gtest-1.7.0 src)
	enable_testing()
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	add_executable(runUnitTests test/snametize_test.cc)
	target_link_libraries(runUnitTests gtest gtest_main)
	target_link_libraries(runUnitTests snametize_lib ${Boost_PROGRAM_OPTIONS_LIBRARY})
	add_test(NAME snametizeUnitTests COMMAND runUnitTests)
endif() 
