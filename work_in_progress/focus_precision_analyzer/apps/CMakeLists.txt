
set(HEADER_LIST "${CLI_App_Framework_SOURCE_DIR}/extern/clipp/clipp.hpp")
set(HEADER_LIST "${CLI_App_Framework_SOURCE_DIR}/include/input_validators++/validators.hpp")

add_executable(app app.cpp)

target_include_directories(app PRIVATE ../extern/clipp)
target_include_directories(app PRIVATE ../include)

target_compile_features(app PRIVATE cxx_std_17)

target_link_libraries(app PRIVATE input_validators++ Qt::Core)
