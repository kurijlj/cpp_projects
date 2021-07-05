###############################################################################
# Generic CMake file
###############################################################################

# Works with 3.15 and tested through 3.20
cmake_minimum_required(VERSION 3.15...3.20)

# Project name and a few useful settings. Other commands can pick up the results
project(
    CMake_Compiler_Flags
    VERSION 0.1
    DESCRIPTION "Custom to show default flags for selected C++ compiler"
    LANGUAGES CXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")
    message("C++ compiler Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
    message("C++ compiler MinSizeRel flags: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
    message("C++ compiler Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
    message("C++ compiler RelWithDebInfo flags: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
endif()
