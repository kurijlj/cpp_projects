# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
foreach(p
    ## Only policies introduced after the cmake_minimum_required
    ## version need to explicitly be set to NEW.
    CMP0070 #3.10.0 Define ``file(GENERATE)`` behavior for relative paths.
    CMP0071 #3.10.0 Let ``AUTOMOC`` and ``AUTOUIC`` process ``GENERATED`` files.
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()


# This project is designed to be built outside the Insight source tree.
project(ITK_TIFF_Test)

# Find Google Test.
find_package(GTest)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Add custom include directories.
include_directories(${PROJECT_SOURCE_DIR}\\include)

add_executable(itk_tiff_test main.cpp validators.cpp)

target_link_libraries(itk_tiff_test ${ITK_LIBRARIES})
