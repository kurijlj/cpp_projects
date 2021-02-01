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
DIR_TEST_VALIDATORS = .\test_validators
DIR_TEST_VALIDATORS_NEW = .\test_validators_new

# Intermediate objects
PDB = $(NAME).pdb
OBJS = *.o
ILKS = *.ilk

# Compiler options
CXX = clang++.exe
CXXFLAGS = -c -pipe -std=c++17 -g -O0 -v -pedantic -Wall -Wextra -fcolor-diagnostics -fdiagnostics-format=vi

# Linker options
LINKER = clang++.exe
LFLAGS = -fcolor-diagnostics -Wl,/debug,/pdb:$(PDB)

# Libraries
INCPATH = -I..\include
LIBS_USER = 


# Build tests #################################################################
test_validators: test_validators_dir test_validators.o validators.o
	@cd $(DIR_TEST_VALIDATORS)
	$(LINKER) $(LFLAGS) -o $(TARGET) test_validators.o validators.o
	@cd ..

test_validators_new: test_validators_new_dir test_validators_new.o validators_new.o
	@cd $(DIR_TEST_VALIDATORS_NEW)
	$(LINKER) $(LFLAGS) -o $(TARGET) test_validators_new.o validators_new.o
	@cd ..


# Build prerequisites #########################################################

# Sub-directories
test_validators_dir:
	@if not exist $(DIR_TEST_VALIDATORS) mkdir $(DIR_TEST_VALIDATORS)

test_validators_new_dir:
	@if not exist $(DIR_TEST_VALIDATORS_NEW) mkdir $(DIR_TEST_VALIDATORS_NEW)

# Object files
test_validators.o:
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(DIR_TEST_VALIDATORS)\test_validators.o test_validators.cpp

test_validators_new.o:
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(DIR_TEST_VALIDATORS_NEW)\test_validators_new.o test_validators_new.cpp

validators.o:
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(DIR_TEST_VALIDATORS)\validators.o ..\validators.cpp

validators_new.o:
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(DIR_TEST_VALIDATORS_NEW)\validators_new.o ..\validators.cpp


# Show help ###################################################################
help :
	@echo Usage: nmake [OPTION]
	@echo.
	@echo * Help options
	@echo [help] - show this help message and exit
	@echo.
	@echo * Build options
	@echo [test_validators] - compile unit testing code for validators.cpp
	@echo [test_validators_new] - compile unit testing code for validators.cpp
	@echo.
	@echo * Clean options
	@echo [clean] - clear object files from previous build
	@echo [cleanall] - clear all files from previous build


# Clean intermediate files ####################################################
clean: clean_test_validators clean_test_validators_new

clean_test_validators :
	@if exist $(DIR_TEST_VALIDATORS) (@del $(DIR_TEST_VALIDATORS)\$(OBJS) $(DIR_TEST_VALIDATORS)\$(PDB) $(DIR_TEST_VALIDATORS)\$(ILKS))

clean_test_validators_new :
	@if exist $(DIR_TEST_VALIDATORS_NEW) (@del $(DIR_TEST_VALIDATORS_NEW)\$(OBJS) $(DIR_TEST_VALIDATORS_NEW)\$(PDB) $(DIR_TEST_VALIDATORS_NEW)\$(ILKS))


# Clean everything except sources #############################################
cleanall : cleanall_test_validators cleanall_test_validators_new

cleanall_test_validators :
	@if exist $(DIR_TEST_VALIDATORS) (@rmdir /S /Q $(DIR_TEST_VALIDATORS))

cleanall_test_validators_new :
	@if exist $(DIR_TEST_VALIDATORS_NEW) (@rmdir /S /Q $(DIR_TEST_VALIDATORS_NEW))
