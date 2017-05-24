cmake_minimum_required(VERSION 3.2)
project(demo)

find_package(Threads REQUIRED)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	#gcc
	set(CMAKE_CXX_FLAGS "-g")
	execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
					OUTPUT_VARIABLE COMPILER_VERSION)
	if (COMPILER_VERSION VERSION_GREATER 4.7 OR COMPILER_VERSION VERSION_EQUAL 4.7)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	endif()
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
	#Clang and AppleClang
	set(CMAKE_CXX_FLAGS "-g")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# using Visual Studio C++
	# -D_WIN32_WINNT=0x0501 to shut up asio warning
	# /EHsc to shut up C++ exception handling was used but /EHsc was not selected.
	set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0501 /EHsc /utf-8")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else ()
	# default
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

include_directories(
	googletest/googletest
	googletest/googletest/include
)
set(TEST_FILES
	googletest/googletest/src/gtest-all.cc
	googletest/googletest/src/gtest_main.cc
	lambda_test.cpp
	raii_test.cpp)

add_executable(${PROJECT_NAME} ${TEST_FILES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
