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
NAME = test
TARGET = $(NAME).exe

# Output directories
DIR_LIBTIFF_INTERFACE = .\test_libtiff_interface

# Intermediate objects
PDB = $(NAME).pdb
OBJS = *.o
ILKS = *.ilk

# Compiler options
CXX = clang++.exe
CXXFLAGS = -c -pipe -std=c++17 -g -O0 -v -pedantic -Wall -Wextra -fcolor-diagnostics -fdiagnostics-format=vi

# Linker options
LINKER = clang++.exe
LFLAGS = -fcolor-diagnostics -Wl,/nologo,/verbose,/debug,/pdb:$(PDB)

# Libraries
INCPATH = -I..\include -I..\libtiff
LIBS_USER = ..\..\libtiff\libtiff_i.lib


# Build tests #################################################################
libtiff_interface: libtiff_interface_dir libtiff_interface.o
	@cd $(DIR_LIBTIFF_INTERFACE)
	$(LINKER) $(LFLAGS) -o $(TARGET) libtiff_interface.o $(LIBS_USER)
	copy ..\..\libtiff\libtiff.dll
	@cd ..


# Build prerequisites #########################################################

# Sub-directories
libtiff_interface_dir:
	@if not exist $(DIR_LIBTIFF_INTERFACE) mkdir $(DIR_LIBTIFF_INTERFACE)

# Object files
libtiff_interface.o:
	$(CXX) $(CXXFLAGS) $(INCPATH) \
		-o $(DIR_LIBTIFF_INTERFACE)\libtiff_interface.o \
		test_libtiff_interface.cpp


# Show help ###################################################################
help :
	@echo Usage: nmake [OPTION]
	@echo.
	@echo * Help options
	@echo [help] - show this help message and exit
	@echo.
	@echo * Build options
	@echo [libtiff_interface] - compile unit testing code for \
		LibTIFFInterface class
	@echo.
	@echo * Clean options
	@echo [clean] - clear object files from previous build
	@echo [clean_libtiff_interface] - clear object files from previous build
	@echo [cleanall] - clear all files from previous build
	@echo [cleanall_libtiff_interface] - clear all files from previous build


# Clean intermediate files ####################################################
clean: clean_libtiff_interface

clean_libtiff_interface :
	@if exist $(DIR_LIBTIFF_INTERFACE) (@del $(DIR_LIBTIFF_INTERFACE)\$(OBJS) \
		$(DIR_LIBTIFF_INTERFACE)\$(PDB) \
		$(DIR_LIBTIFF_INTERFACE)\$(ILKS))


# Clean everything except sources #############################################
cleanall : cleanall_libtiff_interface

cleanall_libtiff_interface :
	@if exist $(DIR_LIBTIFF_INTERFACE) (@rmdir /S /Q $(DIR_LIBTIFF_INTERFACE))
