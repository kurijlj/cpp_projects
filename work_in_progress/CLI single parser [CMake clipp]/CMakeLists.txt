###############################################################################
# Generic CMake file
###############################################################################

# Set CMake requirements
cmake_minimum_required(VERSION 3.9)

# Downgrade policy level for versions lower than 3.20
if(${CMAKE_VERSION} VERSION_LESS 3.20)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.20)
endif()

# Set the project name
project(CLI_App_Framework VERSION 0.1
    DESCRIPTION "Framework for developing CLI applications"
    LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add custom include directories.
target_include_directories(app PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Add the executable
add_executable(app main.cpp validators.cpp validators.hpp clipp.hpp)
