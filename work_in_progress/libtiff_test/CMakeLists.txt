# Ste CMake requirements
cmake_minimum_required(VERSION 3.19.6 FATAL_ERROR)

# Set the project name
project(libtiff_test)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add custom include directories.
include_directories(${PROJECT_SOURCE_DIR}\\include)

add_executable(itk_tiff_test main.cpp validators.cpp)

target_link_libraries(itk_tiff_test ${ITK_LIBRARIES})
