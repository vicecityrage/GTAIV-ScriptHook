cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(ScriptHook)

file(GLOB_RECURSE SCRIPTHOOK_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(ScriptHook STATIC ${SCRIPTHOOK_HEADERS})
set_target_properties(ScriptHook PROPERTIES LINKER_LANGUAGE CXX)

if (UNIX)
	message(FATAL_ERROR "ScriptHook cannot be compiled on Linux.")
endif()

if (MSVC)
	# We're using good old MSVC.
	add_compile_options(/std:c++17)
else()
	# Safe to assume we're either using MinGW or Cygwin.
	add_compile_options(-m32 -std=c++17)
endif()

set(SCRIPTHOOK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SCRIPTHOOK_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if (NOT SCRIPTHOOK_TESTS)
	message(STATUS "Enabling Tests")

	# FiberThread
	add_subdirectory(tests/fiberthread)
endif()