cmake_minimum_required(VERSION 3.15...3.20)

project(
    opencv_tiff_validator
    VERSION 0.1
    DESCRIPTION "Validate TIFF files using OpenCV library"
    LANGUAGES C CXX
    )

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV components
#if("Windows" STREQUAL ${CMAKE_SYSTEM_NAME} AND DEFINED OpenCV_PATH)
if(WIN32 AND DEFINED OpenCV_PATH)
    find_package(OpenCV COMPONENTS core REQUIRED HINTS ${OpenCV_PATH})
    find_package(OpenCV COMPONENTS imgcodecs REQUIRED HINTS ${OpenCV_PATH})
    find_package(OpenCV COMPONENTS highgui REQUIRED HINTS ${OpenCV_PATH})
else()
    find_package(OpenCV COMPONENTS core REQUIRED)
    find_package(OpenCV COMPONENTS imgcodecs REQUIRED)
    find_package(OpenCV COMPONENTS highgui REQUIRED)
endif()

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

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
