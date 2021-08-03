# Note that headers are optional, and do not affect add_library, but they will
# not show up in IDEs unless they are listed in add_library.
set(HEADER_LIST "${CLI_App_Framework_SOURCE_DIR}/extern/lest/lest.hpp")
set(HEADER_LIST "${CLI_App_Framework_SOURCE_DIR}/extern/armadillo/include/armadillo")

# Tests need to be added as executables first
#add_executable(test_validators_1 test_validators_1.cpp)
#add_executable(test_validators_2 test_validators_2.cpp)
add_executable(test_table_view
    test_table_view.cpp
    ../apps/table_view_widget.cpp ../apps/table_view_widget.hpp
    ../apps/data_model.cpp ../apps/data_model.hpp
    ../apps/custom_header_view.cpp ../apps/custom_header_view.hpp
    )

#target_include_directories(test_validators_1 PRIVATE ../extern/lest)
#target_include_directories(test_validators_2 PRIVATE ../extern/lest)
target_include_directories(test_table_view PRIVATE
    ../extern/armadillo/include
    ../apps
    )

# I'm using C++17 in the test
#target_compile_features(test_validators_1 PRIVATE cxx_std_17)
#target_compile_features(test_validators_2 PRIVATE cxx_std_17)
target_compile_features(test_table_view PRIVATE cxx_std_17)

# Should be linked to the main library
#target_link_libraries(test_validators_1 PRIVATE input_validators++)
#target_link_libraries(test_validators_2 PRIVATE input_validators++)
target_link_libraries(test_table_view PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
    armadillo
    )

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
#add_test(NAME test_validators_1 COMMAND test_validators_1) # Command can be a target
#add_test(NAME test_validators_2 COMMAND test_validators_2) # Command can be a target
add_test(NAME test_table_view COMMAND test_table_view) # Command can be a target

# Copy test data to binary tree
# file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data")
#file(COPY "${CLI_App_Framework_SOURCE_DIR}/tests/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
#file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data/empty_dir")
