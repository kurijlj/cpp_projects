# Note that headers are optional, and do not affect add_library, but they will
# not show up in IDEs unless they are listed in add_library.
set(HEADER_LIST "${tiffio++_SOURCE_DIR}/extern/lest/lest.hpp")
set(HEADER_LIST "${tiffio++_SOURCE_DIR}/include/tiffio++/tiffio++.hpp")

# Tests need to be added as executables first
add_executable(test_exception_class test_exception_class.cpp)
add_executable(test_fileaccessmode_class test_fileaccessmode_class.cpp)
add_executable(test_tiffio_openclose test_tiffio_openclose.cpp)
add_executable(test_tiffio_tag test_tiffio_tag.cpp)

target_include_directories(test_exception_class PRIVATE ../extern/lest)
target_include_directories(test_exception_class PRIVATE ../extern/libtiff)
target_include_directories(test_exception_class PRIVATE ../include)
target_include_directories(test_fileaccessmode_class PRIVATE ../extern/lest)
target_include_directories(test_fileaccessmode_class PRIVATE ../extern/libtiff)
target_include_directories(test_fileaccessmode_class PRIVATE ../include)
target_include_directories(test_tiffio_openclose PRIVATE ../extern/lest)
target_include_directories(test_tiffio_openclose PRIVATE ../extern/libtiff)
target_include_directories(test_tiffio_openclose PRIVATE ../include)
target_include_directories(test_tiffio_tag PRIVATE ../extern/lest)
target_include_directories(test_tiffio_tag PRIVATE ../extern/libtiff)
target_include_directories(test_tiffio_tag PRIVATE ../include)


# I'm using C++17 in the test
target_compile_features(test_exception_class PRIVATE cxx_std_17)
target_compile_features(test_fileaccessmode_class PRIVATE cxx_std_17)
target_compile_features(test_tiffio_openclose PRIVATE cxx_std_17)
target_compile_features(test_tiffio_tag PRIVATE cxx_std_17)

# Should be linked to the main library
target_link_libraries(test_exception_class PRIVATE tiff)
target_link_libraries(test_fileaccessmode_class PRIVATE tiff)
target_link_libraries(test_tiffio_openclose PRIVATE tiff)
target_link_libraries(test_tiffio_tag PRIVATE tiff)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME test_exception_class COMMAND test_exception_class) # Command can be a target
add_test(NAME test_fileaccessmode_class COMMAND test_fileaccessmode_class) # Command can be a target
add_test(NAME test_tiffio_openclose COMMAND test_tiffio_openclose) # Command can be a target
add_test(NAME test_tiffio_tag COMMAND test_tiffio_tag) # Command can be a target

# Copy test data to binary tree
# file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data")
file(COPY "${tiffio++_SOURCE_DIR}/tests/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
# file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data/empty_dir")
