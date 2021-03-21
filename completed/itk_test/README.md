
How to compile
==============

Using MS Visual Studio
----------------------

To build VS project run:

```
> cmake -DITK_DIR="C:\UserBuilds\build\ITK"
> msbuild -property:Configuration=<Debug | Release> ALL_BUILD.vcxproj
> copy ucrtbased.dll .\<Debug | Release >
```
