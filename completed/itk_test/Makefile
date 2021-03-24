###############################################################################
## Copyright (C) <yyyy> <Author Name> <author@mail.com>
##
## This file is part of <program name>.
##
## <program name> is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.
##
###############################################################################


###############################################################################
##
## <Put documentation here>
##
## yyyy-mm-dd <Author Name> <author@mail.com>
##
## * Makefile: created.
##
###############################################################################


###############################################################################
##
## References (this section should be deleted in the release version)
##
## * For documentation on nmake visit:
##   <https://docs.microsoft.com/en-us/cpp/build/reference/nmake-reference>
##   <http://psy.swansea.ac.uk/staff/carter/Compiling/compilation_make.htm>
##
## * Compile it with Visual Studio Build Tools 2017 (compiler >= 19.11.25547)
##
##
###############################################################################


# Macros definitions ##########################################################

# Names
NAME_APP = itk_test

# Targets
TARGET_APP = $(NAME_APP).exe

# Output directories
DIR_DEBUG = .\debug
DIR_RELEASE = .\release
DIR_SANITIZER = .\address_sanitizer

# Intermediate objects
PDB_APP = $(NAME_APP).pdb
OBJS = *.o
ILKS = *.ilk
EXPS = *.exp
LIBS = *.lib
DLLS = *.dll

# Load ITK options
# CXXDEFINES_ITK = -DH5_BUILT_AS_DYNAMIC_LIB -DITK_IO_FACTORY_REGISTER_MANAGER \
# 				 -DCLANG
CXXDEFINES_ITK = -DITK_IO_FACTORY_REGISTER_MANAGER -DCLANG
ITK_DIR = C:\ITK\build\5.2
ITK_INCLUDE = $(ITK_DIR)\include\ITK-5.2
ITK_LIB = $(ITK_DIR)\lib

# Compiler options
ARCH = x64
CXXSTD = c++17
CC = clang-cl
CXX = clang-cl
CXXFLAGS = /c /std:$(CXXSTD) /GX /W4 --analyze -fcolor-diagnostics \
	-fdiagnostics-absolute-paths -v
CXXDEFINES = $(CXXDEFINES_ITK)
CXXDEBUG = /O0 -fstandalone-debug
CXXSANIT = /O1 -fstandalone-debug
CXXRELEASE = /O2

# Linker options
LINKER = lld-link
LFLAGS = /machine:$(ARCH) /libpath:$(ITK_LIB) --color-diagnostics
LFLDEBUG = /debug /pdb:$(PDB_APP)
LFLSANIT = /debug
LFLRELEASE =

# Libraries
INCPATH = $(ITK_INCLUDE)
LIBS_USER = $(ITK_LIB)\itkdouble-conversion-5.2.lib \
$(ITK_LIB)\itksys-5.2.lib \
$(ITK_LIB)\itkvnl_algo-5.2.lib \
$(ITK_LIB)\itkvnl-5.2.lib \
$(ITK_LIB)\itkv3p_netlib-5.2.lib \
$(ITK_LIB)\itkvcl-5.2.lib \
$(ITK_LIB)\itkNetlibSlatec-5.2.lib \
$(ITK_LIB)\itkzlib-5.2.lib \
$(ITK_LIB)\ITKMetaIO-5.2.lib \
$(ITK_LIB)\ITKPath-5.2.lib \
$(ITK_LIB)\ITKLabelMap-5.2.lib \
$(ITK_LIB)\ITKFastMarching-5.2.lib \
$(ITK_LIB)\ITKPolynomials-5.2.lib \
$(ITK_LIB)\ITKBiasCorrection-5.2.lib \
$(ITK_LIB)\ITKColormap-5.2.lib \
$(ITK_LIB)\ITKConvolution-5.2.lib \
$(ITK_LIB)\ITKDICOMParser-5.2.lib \
$(ITK_LIB)\ITKDeformableMesh-5.2.lib \
$(ITK_LIB)\ITKDenoising-5.2.lib \
$(ITK_LIB)\ITKDiffusionTensorImage-5.2.lib \
$(ITK_LIB)\ITKEXPAT-5.2.lib \
$(ITK_LIB)\itkgdcmDICT-5.2.lib \
$(ITK_LIB)\itkgdcmMSFF-5.2.lib \
$(ITK_LIB)\ITKznz-5.2.lib \
$(ITK_LIB)\ITKniftiio-5.2.lib \
$(ITK_LIB)\ITKgiftiio-5.2.lib \
$(ITK_LIB)\ITKPDEDeformableRegistration-5.2.lib \
$(ITK_LIB)\ITKIOBioRad-5.2.lib \
$(ITK_LIB)\ITKIOBruker-5.2.lib \
$(ITK_LIB)\ITKIOCSV-5.2.lib \
$(ITK_LIB)\ITKIOGE-5.2.lib \
$(ITK_LIB)\ITKIOHDF5-5.2.lib \
$(ITK_LIB)\itkjpeg-5.2.lib \
$(ITK_LIB)\itkopenjpeg-5.2.lib \
$(ITK_LIB)\ITKIOJPEG2000-5.2.lib \
$(ITK_LIB)\itktiff-5.2.lib \
$(ITK_LIB)\ITKIOLSM-5.2.lib \
$(ITK_LIB)\itkminc2-5.2.lib \
$(ITK_LIB)\ITKIOMINC-5.2.lib \
$(ITK_LIB)\ITKIOMRC-5.2.lib \
$(ITK_LIB)\ITKNrrdIO-5.2.lib \
$(ITK_LIB)\itkpng-5.2.lib \
$(ITK_LIB)\ITKIOSiemens-5.2.lib \
$(ITK_LIB)\itkdouble-conversion-5.2.lib \
$(ITK_LIB)\itksys-5.2.lib \
$(ITK_LIB)\itkvnl_algo-5.2.lib \
$(ITK_LIB)\itkvnl-5.2.lib \
$(ITK_LIB)\itkdouble-conversion-5.2.lib \
$(ITK_LIB)\itksys-5.2.lib \
$(ITK_LIB)\itkvnl_algo-5.2.lib \
$(ITK_LIB)\itkvnl-5.2.lib \
$(ITK_LIB)\itkv3p_netlib-5.2.lib \
$(ITK_LIB)\itkvcl-5.2.lib \
$(ITK_LIB)\itkNetlibSlatec-5.2.lib \
$(ITK_LIB)\itkzlib-5.2.lib \
$(ITK_LIB)\ITKMetaIO-5.2.lib \
$(ITK_LIB)\ITKPath-5.2.lib \
$(ITK_LIB)\ITKLabelMap-5.2.lib \
$(ITK_LIB)\ITKFastMarching-5.2.lib \
$(ITK_LIB)\ITKPolynomials-5.2.lib \
$(ITK_LIB)\ITKBiasCorrection-5.2.lib \
$(ITK_LIB)\ITKColormap-5.2.lib \
$(ITK_LIB)\ITKConvolution-5.2.lib \
$(ITK_LIB)\ITKDICOMParser-5.2.lib \
$(ITK_LIB)\ITKDeformableMesh-5.2.lib \
$(ITK_LIB)\ITKDenoising-5.2.lib \
$(ITK_LIB)\ITKDiffusionTensorImage-5.2.lib \
$(ITK_LIB)\ITKEXPAT-5.2.lib \
$(ITK_LIB)\itkgdcmDICT-5.2.lib \
$(ITK_LIB)\itkgdcmMSFF-5.2.lib \
$(ITK_LIB)\ITKznz-5.2.lib \
$(ITK_LIB)\ITKniftiio-5.2.lib \
$(ITK_LIB)\ITKgiftiio-5.2.lib \
$(ITK_LIB)\ITKPDEDeformableRegistration-5.2.lib \
$(ITK_LIB)\ITKIOBioRad-5.2.lib \
$(ITK_LIB)\ITKIOBruker-5.2.lib \
$(ITK_LIB)\ITKIOCSV-5.2.lib \
$(ITK_LIB)\ITKIOGE-5.2.lib \
$(ITK_LIB)\ITKIOHDF5-5.2.lib \
$(ITK_LIB)\itkjpeg-5.2.lib \
$(ITK_LIB)\itkopenjpeg-5.2.lib \
$(ITK_LIB)\ITKIOJPEG2000-5.2.lib \
$(ITK_LIB)\itktiff-5.2.lib \
$(ITK_LIB)\ITKIOLSM-5.2.lib \
$(ITK_LIB)\itkminc2-5.2.lib \
$(ITK_LIB)\ITKIOMINC-5.2.lib \
$(ITK_LIB)\ITKIOMRC-5.2.lib \
$(ITK_LIB)\ITKNrrdIO-5.2.lib \
$(ITK_LIB)\itkpng-5.2.lib \
$(ITK_LIB)\ITKIOSiemens-5.2.lib \
$(ITK_LIB)\ITKIOSpatialObjects-5.2.lib \
$(ITK_LIB)\ITKIOStimulate-5.2.lib \
$(ITK_LIB)\ITKTransformFactory-5.2.lib \
$(ITK_LIB)\ITKIOTransformHDF5-5.2.lib \
$(ITK_LIB)\ITKIOTransformInsightLegacy-5.2.lib \
$(ITK_LIB)\ITKIOTransformMatlab-5.2.lib \
$(ITK_LIB)\ITKKLMRegionGrowing-5.2.lib \
$(ITK_LIB)\itklbfgs-5.2.lib \
$(ITK_LIB)\ITKMarkovRandomFieldsClassifiers-5.2.lib \
$(ITK_LIB)\ITKQuadEdgeMeshFiltering-5.2.lib \
$(ITK_LIB)\ITKRegionGrowing-5.2.lib \
$(ITK_LIB)\ITKRegistrationMethodsv4-5.2.lib \
$(ITK_LIB)\ITKTestKernel-5.2.lib \
$(ITK_LIB)\ITKVTK-5.2.lib \
$(ITK_LIB)\ITKVideoIO-5.2.lib \
$(ITK_LIB)\ITKWatersheds-5.2.lib \
$(ITK_LIB)\ITKFFT-5.2.lib \
$(ITK_LIB)\itkgdcmDICT-5.2.lib \
$(ITK_LIB)\itkgdcmIOD-5.2.lib \
$(ITK_LIB)\itkgdcmDSED-5.2.lib \
$(ITK_LIB)\itkgdcmCommon-5.2.lib \
crypt32.lib \
$(ITK_LIB)\itkgdcmjpeg8-5.2.lib \
$(ITK_LIB)\itkgdcmjpeg12-5.2.lib \
$(ITK_LIB)\itkgdcmjpeg16-5.2.lib \
$(ITK_LIB)\itkgdcmopenjp2-5.2.lib \
$(ITK_LIB)\itkgdcmcharls-5.2.lib \
rpcrt4.lib \
$(ITK_LIB)\ITKEXPAT-5.2.lib \
$(ITK_LIB)\ITKniftiio-5.2.lib \
$(ITK_LIB)\ITKznz-5.2.lib \
$(ITK_LIB)\itkjpeg-5.2.lib \
$(ITK_LIB)\ITKIOIPL-5.2.lib \
$(ITK_LIB)\ITKIOXML-5.2.lib \
$(ITK_LIB)\itkhdf5_cpp-shared-5.2_D.lib \
$(ITK_LIB)\itkhdf5-shared-5.2_D.lib \
$(ITK_LIB)\ITKIOTransformBase-5.2.lib \
$(ITK_LIB)\ITKTransformFactory-5.2.lib \
$(ITK_LIB)\ITKImageFeature-5.2.lib \
$(ITK_LIB)\ITKOptimizersv4-5.2.lib \
$(ITK_LIB)\ITKOptimizers-5.2.lib \
$(ITK_LIB)\ITKIOBMP-5.2.lib \
$(ITK_LIB)\ITKIOGDCM-5.2.lib \
$(ITK_LIB)\ITKIOGIPL-5.2.lib \
$(ITK_LIB)\ITKIOJPEG-5.2.lib \
$(ITK_LIB)\ITKIOTIFF-5.2.lib \
$(ITK_LIB)\ITKIOMeshBYU-5.2.lib \
$(ITK_LIB)\ITKIOMeshFreeSurfer-5.2.lib \
$(ITK_LIB)\ITKIOMeshGifti-5.2.lib \
$(ITK_LIB)\ITKIOMeshOBJ-5.2.lib \
$(ITK_LIB)\ITKIOMeshOFF-5.2.lib \
$(ITK_LIB)\ITKIOMeshVTK-5.2.lib \
$(ITK_LIB)\ITKIOMeshBase-5.2.lib \
$(ITK_LIB)\ITKQuadEdgeMesh-5.2.lib \
$(ITK_LIB)\ITKIOMeta-5.2.lib \
$(ITK_LIB)\ITKMetaIO-5.2.lib \
$(ITK_LIB)\itkzlib-5.2.lib \
comctl32.lib \
wsock32.lib \
$(ITK_LIB)\ITKIONIFTI-5.2.lib \
$(ITK_LIB)\ITKIONRRD-5.2.lib \
$(ITK_LIB)\ITKIOPNG-5.2.lib \
$(ITK_LIB)\ITKIOVTK-5.2.lib \
$(ITK_LIB)\ITKIOImageBase-5.2.lib \
$(ITK_LIB)\ITKVideoCore-5.2.lib \
$(ITK_LIB)\ITKMathematicalMorphology-5.2.lib \
$(ITK_LIB)\ITKStatistics-5.2.lib \
$(ITK_LIB)\itkNetlibSlatec-5.2.lib \
$(ITK_LIB)\ITKSpatialObjects-5.2.lib \
$(ITK_LIB)\ITKMesh-5.2.lib \
$(ITK_LIB)\ITKTransform-5.2.lib \
$(ITK_LIB)\ITKPath-5.2.lib \
$(ITK_LIB)\ITKCommon-5.2.lib \
$(ITK_LIB)\itksys-5.2.lib \
ws2_32.lib \
dbghelp.lib \
psapi.lib \
$(ITK_LIB)\ITKVNLInstantiation-5.2.lib \
$(ITK_LIB)\itkvnl_algo-5.2.lib \
$(ITK_LIB)\itkvnl-5.2.lib \
$(ITK_LIB)\itkv3p_netlib-5.2.lib \
$(ITK_LIB)\itkvcl-5.2.lib \
$(ITK_LIB)\ITKSmoothing-5.2.lib \
kernel32.lib \
user32.lib \
gdi32.lib \
winspool.lib \
shell32.lib \
ole32.lib \
oleaut32.lib \
uuid.lib \
comdlg32.lib \
advapi32.lib \
$(ITK_LIB)\itkv3p_netlib-5.2.lib \
$(ITK_LIB)\itkvcl-5.2.lib \
$(ITK_LIB)\itkNetlibSlatec-5.2.lib \
$(ITK_LIB)\itkzlib-5.2.lib \
$(ITK_LIB)\ITKMetaIO-5.2.lib \
$(ITK_LIB)\ITKPath-5.2.lib \
$(ITK_LIB)\ITKLabelMap-5.2.lib \
$(ITK_LIB)\ITKFastMarching-5.2.lib \
$(ITK_LIB)\ITKPolynomials-5.2.lib \
$(ITK_LIB)\ITKBiasCorrection-5.2.lib \
$(ITK_LIB)\ITKColormap-5.2.lib \
$(ITK_LIB)\ITKConvolution-5.2.lib \
$(ITK_LIB)\ITKDICOMParser-5.2.lib \
$(ITK_LIB)\ITKDeformableMesh-5.2.lib \
$(ITK_LIB)\ITKDenoising-5.2.lib \
$(ITK_LIB)\ITKDiffusionTensorImage-5.2.lib \
$(ITK_LIB)\ITKEXPAT-5.2.lib \
$(ITK_LIB)\itkgdcmDICT-5.2.lib \
$(ITK_LIB)\itkgdcmMSFF-5.2.lib \
$(ITK_LIB)\ITKznz-5.2.lib \
$(ITK_LIB)\ITKniftiio-5.2.lib \
$(ITK_LIB)\ITKgiftiio-5.2.lib \
$(ITK_LIB)\ITKPDEDeformableRegistration-5.2.lib \
$(ITK_LIB)\ITKIOBioRad-5.2.lib \
$(ITK_LIB)\ITKIOBruker-5.2.lib \
$(ITK_LIB)\ITKIOCSV-5.2.lib \
$(ITK_LIB)\ITKIOGE-5.2.lib \
$(ITK_LIB)\ITKIOHDF5-5.2.lib \
$(ITK_LIB)\itkjpeg-5.2.lib \
$(ITK_LIB)\itkopenjpeg-5.2.lib \
$(ITK_LIB)\ITKIOJPEG2000-5.2.lib \
$(ITK_LIB)\itktiff-5.2.lib \
$(ITK_LIB)\ITKIOLSM-5.2.lib \
$(ITK_LIB)\itkminc2-5.2.lib \
$(ITK_LIB)\ITKIOMINC-5.2.lib \
$(ITK_LIB)\ITKIOMRC-5.2.lib \
$(ITK_LIB)\ITKNrrdIO-5.2.lib \
$(ITK_LIB)\itkpng-5.2.lib \
$(ITK_LIB)\ITKIOSiemens-5.2.lib \
$(ITK_LIB)\ITKIOSpatialObjects-5.2.lib \
$(ITK_LIB)\ITKIOStimulate-5.2.lib \
$(ITK_LIB)\ITKTransformFactory-5.2.lib \
$(ITK_LIB)\ITKIOTransformHDF5-5.2.lib \
$(ITK_LIB)\ITKIOTransformInsightLegacy-5.2.lib \
$(ITK_LIB)\ITKIOTransformMatlab-5.2.lib \
$(ITK_LIB)\ITKKLMRegionGrowing-5.2.lib \
$(ITK_LIB)\itklbfgs-5.2.lib \
$(ITK_LIB)\ITKMarkovRandomFieldsClassifiers-5.2.lib \
$(ITK_LIB)\ITKQuadEdgeMeshFiltering-5.2.lib \
$(ITK_LIB)\ITKRegionGrowing-5.2.lib \
$(ITK_LIB)\ITKRegistrationMethodsv4-5.2.lib \
$(ITK_LIB)\ITKTestKernel-5.2.lib \
$(ITK_LIB)\ITKVTK-5.2.lib \
$(ITK_LIB)\ITKVideoIO-5.2.lib \
$(ITK_LIB)\ITKWatersheds-5.2.lib \
$(ITK_LIB)\ITKFFT-5.2.lib \
$(ITK_LIB)\itkgdcmDICT-5.2.lib \
$(ITK_LIB)\itkgdcmIOD-5.2.lib \
$(ITK_LIB)\itkgdcmDSED-5.2.lib \
$(ITK_LIB)\itkgdcmCommon-5.2.lib \
crypt32.lib \
$(ITK_LIB)\itkgdcmjpeg8-5.2.lib \
$(ITK_LIB)\itkgdcmjpeg12-5.2.lib \
$(ITK_LIB)\itkgdcmjpeg16-5.2.lib \
$(ITK_LIB)\itkgdcmopenjp2-5.2.lib \
$(ITK_LIB)\itkgdcmcharls-5.2.lib \
rpcrt4.lib \
$(ITK_LIB)\ITKEXPAT-5.2.lib \
$(ITK_LIB)\ITKniftiio-5.2.lib \
$(ITK_LIB)\ITKznz-5.2.lib \
$(ITK_LIB)\itkjpeg-5.2.lib \
$(ITK_LIB)\ITKIOIPL-5.2.lib \
$(ITK_LIB)\ITKIOXML-5.2.lib \
$(ITK_LIB)\itkhdf5_cpp-shared-5.2_D.lib \
$(ITK_LIB)\itkhdf5-shared-5.2_D.lib \
$(ITK_LIB)\ITKIOTransformBase-5.2.lib \
$(ITK_LIB)\ITKTransformFactory-5.2.lib \
$(ITK_LIB)\ITKImageFeature-5.2.lib \
$(ITK_LIB)\ITKOptimizersv4-5.2.lib \
$(ITK_LIB)\ITKOptimizers-5.2.lib \
$(ITK_LIB)\ITKIOBMP-5.2.lib \
$(ITK_LIB)\ITKIOGDCM-5.2.lib \
$(ITK_LIB)\ITKIOGIPL-5.2.lib \
$(ITK_LIB)\ITKIOJPEG-5.2.lib \
$(ITK_LIB)\ITKIOTIFF-5.2.lib \
$(ITK_LIB)\ITKIOMeshBYU-5.2.lib \
$(ITK_LIB)\ITKIOMeshFreeSurfer-5.2.lib \
$(ITK_LIB)\ITKIOMeshGifti-5.2.lib \
$(ITK_LIB)\ITKIOMeshOBJ-5.2.lib \
$(ITK_LIB)\ITKIOMeshOFF-5.2.lib \
$(ITK_LIB)\ITKIOMeshVTK-5.2.lib \
$(ITK_LIB)\ITKIOMeshBase-5.2.lib \
$(ITK_LIB)\ITKQuadEdgeMesh-5.2.lib \
$(ITK_LIB)\ITKIOMeta-5.2.lib \
$(ITK_LIB)\ITKMetaIO-5.2.lib \
$(ITK_LIB)\itkzlib-5.2.lib \
comctl32.lib \
wsock32.lib \
$(ITK_LIB)\ITKIONIFTI-5.2.lib \
$(ITK_LIB)\ITKIONRRD-5.2.lib \
$(ITK_LIB)\ITKIOPNG-5.2.lib \
$(ITK_LIB)\ITKIOVTK-5.2.lib \
$(ITK_LIB)\ITKIOImageBase-5.2.lib \
$(ITK_LIB)\ITKVideoCore-5.2.lib \
$(ITK_LIB)\ITKMathematicalMorphology-5.2.lib \
$(ITK_LIB)\ITKStatistics-5.2.lib \
$(ITK_LIB)\itkNetlibSlatec-5.2.lib \
$(ITK_LIB)\ITKSpatialObjects-5.2.lib \
$(ITK_LIB)\ITKMesh-5.2.lib \
$(ITK_LIB)\ITKTransform-5.2.lib \
$(ITK_LIB)\ITKPath-5.2.lib \
$(ITK_LIB)\ITKCommon-5.2.lib \
$(ITK_LIB)\itksys-5.2.lib \
ws2_32.lib \
dbghelp.lib \
psapi.lib \
$(ITK_LIB)\ITKVNLInstantiation-5.2.lib \
$(ITK_LIB)\itkvnl_algo-5.2.lib \
$(ITK_LIB)\itkvnl-5.2.lib \
$(ITK_LIB)\itkv3p_netlib-5.2.lib \
$(ITK_LIB)\itkvcl-5.2.lib \
$(ITK_LIB)\ITKSmoothing-5.2.lib \
kernel32.lib \
user32.lib \
gdi32.lib \
winspool.lib \
shell32.lib \
ole32.lib \
oleaut32.lib \
uuid.lib \
comdlg32.lib \
advapi32.lib \
$(ITK_LIB)\ITKIOSpatialObjects-5.2.lib \
$(ITK_LIB)\ITKIOStimulate-5.2.lib \
$(ITK_LIB)\ITKTransformFactory-5.2.lib \
$(ITK_LIB)\ITKIOTransformHDF5-5.2.lib \
$(ITK_LIB)\ITKIOTransformInsightLegacy-5.2.lib \
$(ITK_LIB)\ITKIOTransformMatlab-5.2.lib \
$(ITK_LIB)\ITKKLMRegionGrowing-5.2.lib \
$(ITK_LIB)\itklbfgs-5.2.lib \
$(ITK_LIB)\ITKMarkovRandomFieldsClassifiers-5.2.lib \
$(ITK_LIB)\ITKQuadEdgeMeshFiltering-5.2.lib \
$(ITK_LIB)\ITKRegionGrowing-5.2.lib \
$(ITK_LIB)\ITKRegistrationMethodsv4-5.2.lib \
$(ITK_LIB)\ITKTestKernel-5.2.lib \
$(ITK_LIB)\ITKVTK-5.2.lib \
$(ITK_LIB)\ITKVideoIO-5.2.lib \
$(ITK_LIB)\ITKWatersheds-5.2.lib \
$(ITK_LIB)\ITKFFT-5.2.lib \
$(ITK_LIB)\itkgdcmDICT-5.2.lib \
$(ITK_LIB)\itkgdcmIOD-5.2.lib \
$(ITK_LIB)\itkgdcmDSED-5.2.lib \
$(ITK_LIB)\itkgdcmCommon-5.2.lib \
crypt32.lib \
$(ITK_LIB)\itkgdcmjpeg8-5.2.lib \
$(ITK_LIB)\itkgdcmjpeg12-5.2.lib \
$(ITK_LIB)\itkgdcmjpeg16-5.2.lib \
$(ITK_LIB)\itkgdcmopenjp2-5.2.lib \
$(ITK_LIB)\itkgdcmcharls-5.2.lib \
rpcrt4.lib \
$(ITK_LIB)\ITKEXPAT-5.2.lib \
$(ITK_LIB)\ITKniftiio-5.2.lib \
$(ITK_LIB)\ITKznz-5.2.lib \
$(ITK_LIB)\itkjpeg-5.2.lib \
$(ITK_LIB)\ITKIOIPL-5.2.lib \
$(ITK_LIB)\ITKIOXML-5.2.lib \
$(ITK_LIB)\itkhdf5_cpp-shared-5.2_D.lib \
$(ITK_LIB)\itkhdf5-shared-5.2_D.lib \
$(ITK_LIB)\ITKIOTransformBase-5.2.lib \
$(ITK_LIB)\ITKTransformFactory-5.2.lib \
$(ITK_LIB)\ITKImageFeature-5.2.lib \
$(ITK_LIB)\ITKOptimizersv4-5.2.lib \
$(ITK_LIB)\ITKOptimizers-5.2.lib \
$(ITK_LIB)\ITKIOBMP-5.2.lib \
$(ITK_LIB)\ITKIOGDCM-5.2.lib \
$(ITK_LIB)\ITKIOGIPL-5.2.lib \
$(ITK_LIB)\ITKIOJPEG-5.2.lib \
$(ITK_LIB)\ITKIOTIFF-5.2.lib \
$(ITK_LIB)\ITKIOMeshBYU-5.2.lib \
$(ITK_LIB)\ITKIOMeshFreeSurfer-5.2.lib \
$(ITK_LIB)\ITKIOMeshGifti-5.2.lib \
$(ITK_LIB)\ITKIOMeshOBJ-5.2.lib \
$(ITK_LIB)\ITKIOMeshOFF-5.2.lib \
$(ITK_LIB)\ITKIOMeshVTK-5.2.lib \
$(ITK_LIB)\ITKIOMeshBase-5.2.lib \
$(ITK_LIB)\ITKQuadEdgeMesh-5.2.lib \
$(ITK_LIB)\ITKIOMeta-5.2.lib \
$(ITK_LIB)\ITKMetaIO-5.2.lib \
$(ITK_LIB)\itkzlib-5.2.lib \
comctl32.lib \
wsock32.lib \
$(ITK_LIB)\ITKIONIFTI-5.2.lib \
$(ITK_LIB)\ITKIONRRD-5.2.lib \
$(ITK_LIB)\ITKIOPNG-5.2.lib \
$(ITK_LIB)\ITKIOVTK-5.2.lib \
$(ITK_LIB)\ITKIOImageBase-5.2.lib \
$(ITK_LIB)\ITKVideoCore-5.2.lib \
$(ITK_LIB)\ITKMathematicalMorphology-5.2.lib \
$(ITK_LIB)\ITKStatistics-5.2.lib \
$(ITK_LIB)\itkNetlibSlatec-5.2.lib \
$(ITK_LIB)\ITKSpatialObjects-5.2.lib \
$(ITK_LIB)\ITKMesh-5.2.lib \
$(ITK_LIB)\ITKTransform-5.2.lib \
$(ITK_LIB)\ITKPath-5.2.lib \
$(ITK_LIB)\ITKCommon-5.2.lib \
$(ITK_LIB)\itksys-5.2.lib \
ws2_32.lib \
dbghelp.lib \
psapi.lib \
$(ITK_LIB)\ITKVNLInstantiation-5.2.lib \
$(ITK_LIB)\itkvnl_algo-5.2.lib \
$(ITK_LIB)\itkvnl-5.2.lib \
$(ITK_LIB)\itkv3p_netlib-5.2.lib \
$(ITK_LIB)\itkvcl-5.2.lib \
$(ITK_LIB)\ITKSmoothing-5.2.lib \
kernel32.lib \
user32.lib \
gdi32.lib \
winspool.lib \
shell32.lib \
ole32.lib \
oleaut32.lib \
uuid.lib \
comdlg32.lib \
advapi32.lib \


# Build app ###################################################################
debug : debug_dir main_debug_o
	@cd $(DIR_DEBUG)
	$(LINKER) $(LFLAGS) $(LFLDEBUG) -o $(TARGET_APP) \
		main.o $(LIBS_USER)
	@cd ..

release : release_dir main_release_o
	@cd $(DIR_RELEASE)
	$(LINKER) $(LFLAGS) $(LFLRELEASE) -o $(TARGET_APP) \
		main.o $(LIBS_USER)
	@cd ..

sanitizer : sanitizer_dir main_sanitizer_o
	@cd $(DIR_SANITIZER)
	$(LINKER) $(LFLAGS) $(LFLSANIT) -o $(TARGET_APP) \
		main.o $(LIBS_USER)
	@cd ..


# Build prerequisites #########################################################

# Sub-directories
debug_dir:
	@if not exist $(DIR_DEBUG) mkdir $(DIR_DEBUG)

sanitizer_dir:
	@if not exist $(DIR_SANITIZER) mkdir $(DIR_SANITIZER)

release_dir:
	@if not exist $(DIR_RELEASE) mkdir $(DIR_RELEASE)

# Object files
main_debug_o:
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(CXXDEFINES) /I $(INCPATH) \
		/Fo$(DIR_DEBUG)\main.o main.cpp

main_sanitizer_o:
	$(CXX) $(CXXFLAGS) $(CXXSANIT) $(CXXDEFINES) /I $(INCPATH) \
		/Fo$(DIR_SANITIZER)\main.o main.cpp

main_release_o:
	$(CXX) $(CXXFLAGS) $(CXXRELEASE) $(CXXDEFINES) /I $(INCPATH) \
		/Fo$(DIR_RELEASE)\main.o main.cpp


# Show help ###################################################################
help :
	@echo Usage: nmake [OPTION]
	@echo.
	@echo * Help options
	@echo [help] - show this help message and exit
	@echo.
	@echo * Build options
	@echo [debug] - compile debug version
	@echo [release] - compile release version
	@echo [sanitizer] - compile debug version with address sanitizer option on
	@echo.
	@echo * Cleaning options
	@echo [clean] - clear object files from previous build
	@echo [clean_debug] - clear object files for the debug from previous build
	@echo [clean_release] - clear object files for the release from previous build
	@echo [clean_sanitizer] - clear object files for the sanitizer from previous build
	@echo [cleanall] - clear all files from previous build
	@echo [cleanall_debug] - clear all files for the debug from previous build
	@echo [cleanall_release] - clear all files fir the release from previous build
	@echo [cleanall_sanitizer] - clear all files for the sanitizer from previous build


# Clean intermediate files ####################################################
clean: clean_debug clean_release clean_sanitizer

clean_debug :
	@if exist $(DIR_DEBUG) (@del $(DIR_DEBUG)\$(OBJS) \
		$(DIR_DEBUG)\$(PDB) \
		$(DIR_DEBUG)\$(ILKS) \
		$(DIR_DEBUG)\$(DLLS))

clean_release :
	@if exist $(DIR_RELEASE) (@del $(DIR_RELEASE)\$(OBJS) $(DIR_DEBUG)\$(DLLS))

clean_sanitizer :
	@if exist $(DIR_SANITIZER) (@del $(DIR_SANITIZER)\$(OBJS) \
		$(DIR_SANITIZER)\$(EXPS) \
		$(DIR_SANITIZER)\$(LIBS) \
		$(DIR_DEBUG)\$(DLLS) \
		$(DIR_SANITIZER)\$(PDB))


# Clean everything except sources #############################################
cleanall : cleanall_debug cleanall_release cleanall_sanitizer

cleanall_debug:
	@if exist $(DIR_DEBUG) (@rmdir /S /Q $(DIR_DEBUG))

cleanall_release:
	@if exist $(DIR_RELEASE) (@rmdir /S /Q $(DIR_RELEASE))

cleanall_sanitizer:
	@if exist $(DIR_SANITIZER) (@rmdir /S /Q $(DIR_SANITIZER))
