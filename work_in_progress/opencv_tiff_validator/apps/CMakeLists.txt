set(HEADER_LIST "${PROJECT_SOURCE_DIR}/extern/clipp/clipp.hpp")
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/input_validators++/validators.hpp")

SET(APPS validate_tiff)

SET(INCLUDE_DIRS ../extern/clipp
    ../include
    ${OpenCV_INCLUDE_DIRS}
    )

foreach(program ${APPS})
    add_executable(${program} ${program}.cpp)
    target_include_directories(${program} PRIVATE ${INCLUDE_DIRS})
    target_compile_features(${program} PRIVATE cxx_std_17)
    target_link_libraries(${program} PRIVATE input_validators++
        opencv_core
        opencv_imgcodecs
        opencv_highgui
        )
endforeach(program)
