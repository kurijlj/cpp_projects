
set(HEADER_LIST "${Focus_Precision_Analyzer_SOURCE_DIR}/extern/clipp/clipp.hpp")
set(HEADER_LIST "${Focus_Precision_Analyzer_SOURCE_DIR}/include/input_validators++/validators.hpp")

add_executable(fpt_stat app.cpp)

target_include_directories(fpt_stat PRIVATE ../extern/clipp)
target_include_directories(fpt_stat PRIVATE ../include)

target_compile_features(fpt_stat PRIVATE cxx_std_17)

target_link_libraries(fpt_stat PRIVATE input_validators++)
