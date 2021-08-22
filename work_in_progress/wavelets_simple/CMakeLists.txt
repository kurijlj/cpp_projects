###############################################################################
# Generic CMake file
###############################################################################

# Works with 3.15 and tested through 3.20
cmake_minimum_required(VERSION 3.15...3.20)

# Project name and a few useful settings. Other commands can pick up the results
project(
    wavelets_simple
    VERSION 0.1
    DESCRIPTION "Small C++ application for testing Haar Wavelet Transform"
    LANGUAGES CXX)

# Append custom flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-v -Wall -Wextra -pedantic -fcolor-diagnostics -fdiagnostics-format=vi)
endif()

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endif()

# The compiled library code is here
add_subdirectory(src)

# The Armadillo library code is here
add_subdirectory(extern/armadillo)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
