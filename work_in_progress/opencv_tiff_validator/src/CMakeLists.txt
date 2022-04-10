# Note that headers are optional, and do not affect add_library, but they will
# not show up in IDEs unless they are listed in add_library.
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/input_validators++/validators.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(input_validators++ validators.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(input_validators++ PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(input_validators++ PUBLIC cxx_std_17)
