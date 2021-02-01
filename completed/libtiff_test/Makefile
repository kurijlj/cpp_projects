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
NAME_APP = libtiff_test

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

# Compiler options
CXX = clang++
CXXFLAGS = -c -pipe -std=c++17 -v -pedantic -Wall -Wextra -fcolor-diagnostics -fdiagnostics-format=vi
CXXDEBUG = -g -O0
CXXSANIT = -g -O1 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
CXXRELEASE = -g0 -O2

# Linker options
LINKER = clang++
LFLAGS = -fcolor-diagnostics -Wl,/nologo,/verbose
LFLDEBUG = -Wl,/debug,/pdb:$(PDB_APP)
LFLSANIT = -fsanitize=address -Wl,/debug
LFLRELEASE =

# Libraries
INCPATH = -I.\include -I.\libtiff
LIBS_USER = ..\libtiff\libtiff_i.lib


# Build app ###################################################################
debug : debug_dir main_debug_o validators_debug_o
	@cd $(DIR_DEBUG)
	$(LINKER) $(LFLAGS) $(LFLDEBUG) -o $(TARGET_APP) \
		main.o validators.o $(LIBS_USER)
	copy ..\libtiff\libtiff.dll
	@cd ..

release : release_dir main_release_o validators_release_o
	@cd $(DIR_RELEASE)
	$(LINKER) $(LFLAGS) $(LFLRELEASE) -o $(TARGET_APP) \
		main.o validators.o $(LIBS_USER)
	copy ..\libtiff\libtiff.dll
	@cd ..

sanitizer : sanitizer_dir main_sanitizer_o validators_sanitizer_o
	@cd $(DIR_SANITIZER)
	$(LINKER) $(LFLAGS) $(LFLSANIT) -o $(TARGET_APP) \
		main.o validators.o $(LIBS_USER)
	copy ..\libtiff\libtiff.dll
	@cd ..


# Build prerequisites #########################################################

# Sub-directories
debug_dir:
	@if not exist $(DIR_DEBUG) mkdir $(DIR_DEBUG)

sanitizer_dir:
	@if not exist $(DIR_SANITIZER) mkdir $(DIR_SANITIZER)

release_dir:
	@if not exist $(DIR_RELEASE) mkdir $(DIR_RELEASE)

# Shared libraries
shared:
	@copy .\libtiff\libtiff.dll .\debug

# Object files
main_debug_o:
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(INCPATH) -o $(DIR_DEBUG)\main.o main.cpp

main_sanitizer_o:
	$(CXX) $(CXXFLAGS) $(CXXSANIT) $(INCPATH) -o $(DIR_SANITIZER)\main.o main.cpp

main_release_o:
	$(CXX) $(CXXFLAGS) $(CXXRELEASE) $(INCPATH) -o $(DIR_RELEASE)\main.o main.cpp

validators_debug_o:
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(INCPATH) -o $(DIR_DEBUG)\validators.o validators.cpp

validators_sanitizer_o:
	$(CXX) $(CXXFLAGS) $(CXXSANIT) $(INCPATH) -o $(DIR_SANITIZER)\validators.o validators.cpp

validators_release_o:
	$(CXX) $(CXXFLAGS) $(CXXRELEASE) $(INCPATH) -o $(DIR_RELEASE)\validators.o validators.cpp


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
