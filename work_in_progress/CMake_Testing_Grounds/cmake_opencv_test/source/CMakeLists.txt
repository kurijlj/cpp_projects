cmake_minimum_required(VERSION 3.15)

project(
    cmake_opencv_test
    VERSION 0.1
    DESCRIPTION "Test OpenCV based project configuration linking and compilation"
    LANGUAGES C CXX
    )

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV components
if("Windows" STREQUAL ${CMAKE_SYSTEM_NAME} AND DEFINED OpenCV_PATH)
    #if("Windows" STREQUAL ${CMAKE_SYSTEM_NAME})
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

add_executable(app main.cpp)

target_include_directories(app PRIVATE ${OpenCV_INCLUDE_DIRS})

target_compile_features(app PRIVATE cxx_std_17)

target_link_libraries(app PRIVATE
    opencv_core
    opencv_imgcodecs
    opencv_highgui
    )
