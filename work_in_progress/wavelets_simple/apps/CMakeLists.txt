
set(HEADER_LIST "${wavelets_simple_SOURCE_DIR}/extern/clipp/clipp.hpp")
set(HEADER_LIST "${wavelets_simple_SOURCE_DIR}/extern/armadillo/include/armadillo")
set(HEADER_LIST "${wavelets_simple_SOURCE_DIR}/include/input_validators++/validators.hpp")

add_executable(app app.cpp)

target_include_directories(app PRIVATE
    ../extern/clipp
    ../extern/armadillo/include
    ../include
    )

target_compile_features(app PRIVATE cxx_std_17)

target_link_libraries(app PRIVATE
    input_validators++
    armadillo
    )
