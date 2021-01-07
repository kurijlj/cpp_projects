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
NAME = app
TARGET = $(NAME).exe
PDB = $(NAME).pdb
DIR_SANITIZER = .\address_sanitizer
DIR_DEBUG = .\debug
DIR_RELEASE = .\release
OBJS = *.o
ILKS = *.ilk
EXPS = *.exp
LIBS = *.lib

CXX = clang++
CXXFLAGS = -c -pipe -std=c++17 -v -pedantic -Wall -Wextra -fcolor-diagnostics -fdiagnostics-format=vi
CXXDEBUG = -g -O0
CXXSANIT = -g -O1 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
CXXRELEASE = -g0 -O2
LINKER = clang++
LFLAGS = -fcolor-diagnostics
LFLDEBUG = -Wl,/debug,/pdb:$(PDB)
LFLSANIT = -fsanitize=address -Wl,/debug
LFLRELEASE = 

INCPATH = -I.\include
LIBS_USER = 


# Build app ###################################################################
debug : debug_dir main_debug_o validators_debug_o
	@cd $(DIR_DEBUG)
	$(LINKER) $(LFLAGS) $(LFLDEBUG) -o $(TARGET) main.o validators.o
	@cd ..

sanitizer : sanitizer_dir main_sanitizer_o validators_sanitizer_o
	@cd $(DIR_SANITIZER)
	$(LINKER) $(LFLAGS) $(LFLSANIT) -o $(TARGET) main.o validators.o
	@cd ..

release : release_dir main_release_o validators_release_o
	@cd $(DIR_RELEASE)
	$(LINKER) $(LFLAGS) $(LFLRELEASE) -o $(TARGET) main.o validators.o
	@cd ..


# Build prerequisites #########################################################
debug_dir:
	@if not exist $(DIR_DEBUG) mkdir $(DIR_DEBUG)

sanitizer_dir:
	@if not exist $(DIR_SANITIZER) mkdir $(DIR_SANITIZER)

release_dir:
	@if not exist $(DIR_RELEASE) mkdir $(DIR_RELEASE)

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
	@echo [clean] - clear object files from previous build
	@echo [clean_debug] - clear object files for the debug from previous build
	@echo [clean_release] - clear object files for the release from previous build
	@echo [clean_sanitizer] - clear object files for the sanitizer from previous build
	@echo [cleanall] - clear all files from previous build
	@echo [cleanall_debug] - clear all files for the debug from previous build
	@echo [cleanall_release] - clear all files fir the release from previous build
	@echo [cleanall_sanitizer] - clear all files for the sanitizer from previous build
	@echo [debug] - compile debug version
	@echo [help] - show this help message and exit
	@echo [release] - compile release version


# Clean intermediate files ####################################################
clean_debug :
	@if exist $(DIR_DEBUG) (@del $(DIR_DEBUG)\$(OBJS) $(DIR_DEBUG)\$(PDB) $(DIR_DEBUG)\$(ILKS))

clean_sanitizer :
	@if exist $(DIR_SANITIZER) (@del $(DIR_SANITIZER)\$(OBJS) $(DIR_SANITIZER)\$(EXPS) $(DIR_SANITIZER)\$(LIBS) $(DIR_SANITIZER)\$(PDB))

clean_release :
	@if exist $(DIR_RELEASE) (@del $(DIR_RELEASE)\$(OBJS))

clean: clean_debug clean_sanitizer clean_release


# Clean everything except sources #############################################
clean_debug_all :
	@if exist $(DIR_DEBUG) (@rmdir /S /Q $(DIR_DEBUG))

clean_sanitizer_all :
	@if exist $(DIR_SANITIZER) (@rmdir /S /Q $(DIR_SANITIZER))

clean_release_all :
	@if exist $(DIR_RELEASE) (@rmdir /S /Q $(DIR_RELEASE))

cleanall : clean_debug_all clean_sanitizer_all clean_release_all
