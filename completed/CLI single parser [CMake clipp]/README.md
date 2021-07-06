# CLI Single Parser App Framework [CMake clipp]
Small C++ single parser app framework for developing CLI applications using
"clipp" command line argument parsing library and "CMake" build system.


## Compiling Instructions
Build as regular CMake project:
1. Create build directory and `cd` into it. Than create directory structure and
makefiles using:
`$ cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -G "NMake Makefiles" -S ../.. -B .`

2. Compile using:
`$ make`

Where build paramters can take following values:
```
-DCMAKE_CXX_COMPILER=(clang++/cl/g++/...)
-DCMAKE_BUILD_TYPE=(Debug/RelWithDebInfo/Release/MinSizeRel)
-DBUILD_SHARED_LIBS:BOOL=(TRUE/FALSE)
-DBUILD_TESTING:BOOL=(TRUE/FALSE)
-G ("NMake Makefiles"/"Unix Makefiles"/...)
```
