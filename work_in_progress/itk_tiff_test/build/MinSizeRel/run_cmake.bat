@REM Put comments like this

set BUILD_TYPE=Debug
@REM set Path=C:\ITK\build\1.0\Release\5.2\bin;%Path%

@REM call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
call cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON -DITK_DIR=C:\ITK\build\1.0\Release -G "NMake Makefiles" ..\..
