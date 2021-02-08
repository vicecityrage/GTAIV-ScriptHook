cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(FiberThread)

add_library(FiberThread SHARED main.cpp main.hpp fiberthread.cpp fiberthread.hpp)

target_include_directories(FiberThread PUBLIC ${ScriptHook_SOURCE_DIR}/include)
target_link_libraries(FiberThread ${ScriptHook_SOURCE_DIR}/lib/ScriptHook.lib)

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

message(STATUS "[TESTS] FiberThread")