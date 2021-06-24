@REM Put comments like this
@REM
@REM set Path=C:\ITK\build\1.0\Debug\5.2\bin;%Path%
@REM call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

@REM call cmake -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON -DITK_DIR=C:\ITK\build\1.0\Debug -G "NMake Makefiles" ..\..
call cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON -DITK_DIR=C:\ITK\build\1.0\Debug -G "NMake Makefiles" ..\..
