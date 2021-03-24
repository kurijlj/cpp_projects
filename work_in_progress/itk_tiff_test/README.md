
How to compile
==============

Using MS Visual Studio
----------------------

To build VS project run:

```
> set Path=C:\ITK\build\5.2\bin;%Path%
> mkdir <Debug|Release|RelWithDebInfo|MinSizeRel>
> pushd <Debug|Release|RelWithDebInfo|MinSizeRel>
> cmake -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_BUILD_TYPE=<Debug|Release|RelWithDebInfo|MinSizeRel> -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON -DITK_DIR=C:\ITK\build -G "NMake Makefiles" ..
> nmake
> copy ucrtbased.dll .\
```
