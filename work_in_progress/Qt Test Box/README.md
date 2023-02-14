# Qt Test Box
Small app for testing various Qt library functionalities.


## Compiling Instructions
Build as regular CMake project:
1. Create build directory and `cd` into it. Than create directory structure and
makefiles using:
```
$ cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ../.. -B .
$ make
```

for \*NIX platforms, and:
```
$ cmake -DCMAKE_PREFIX_PATH=C:\Qt\5.15.1\msvc2019_64 -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ../.. -B .
$ msbuild.exe myproject.sln
```

for Win64 platform.

Build paramters can take following values:
```
-DCMAKE_CXX_COMPILER=(clang++/cl/g++/...)
-DCMAKE_BUILD_TYPE=(Debug/RelWithDebInfo/Release/MinSizeRel)
-DBUILD_SHARED_LIBS:BOOL=(TRUE/FALSE)
-DBUILD_TESTING:BOOL=(TRUE/FALSE)
-G ("NMake Makefiles"/"Unix Makefiles"/...)
```
