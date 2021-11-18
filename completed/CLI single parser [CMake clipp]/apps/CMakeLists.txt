
set(HEADER_LIST "${CLI_App_Framework_SOURCE_DIR}/extern/clipp/clipp.hpp")
set(HEADER_LIST "${CLI_App_Framework_SOURCE_DIR}/include/input_validators++/validators.hpp")

SET(APPS app)

SET(INCLUDE_DIRS ../extern/clipp
    ../include
    )

foreach(program ${APPS})
    add_executable(${program} ${program}.cpp)
    target_include_directories(${program} PRIVATE ../extern/clipp)
    target_compile_features(${program} PRIVATE cxx_std_17)
    target_link_libraries(${program} PRIVATE input_validators++)
endforeach(program)
