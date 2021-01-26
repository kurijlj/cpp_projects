###############################################################################
## Copyright (C) 2021 Ljubomir Kurij ljubomir_kurij@protonmail.com
##
## This file is part of CPP Study Cases.
##
## CPP Study Cases is free software: you can redistribute it and/or modify
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
## 2021-01-15 Ljubomir Kurij ljubomir_kurij@protonmail.com
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
NAME_CT = containers
NAME_SP = smart_pointers
NAME_TC = test_clipp

TARGET_CT = $(NAME_CT).exe
TARGET_SP = $(NAME_SP).exe
TARGET_TC = $(NAME_TC).exe

PDB_CT = $(NAME_CT).pdb
PDB_SP = $(NAME_SP).pdb
PDB_TC = $(NAME_TC).pdb

DIR_CT = .\$(NAME_CT)
DIR_SP = .\$(NAME_SP)
DIR_TC = .\$(NAME_TC)

OBJS = *.o
ILKS = *.ilk
EXPS = *.exp
LIBS = *.lib

CXX = clang++
CXXFLAGS = -c -pipe -std=c++17 -g -O0 -v -pedantic -Wall -Wextra -fcolor-diagnostics -fdiagnostics-format=vi
LINKER = clang++
LFLAGS = -fcolor-diagnostics

LFLAGS_CT = -Wl,/debug,/pdb:$(PDB_CT)
LFLAGS_SP = -Wl,/debug,/pdb:$(PDB_SP)
LFLAGS_TC = -Wl,/debug,/pdb:$(PDB_TC)

INCPATH = -I.\include


# Build cases ###################################################################
all : containers smart_pointers test_clipp

containers : ct_dir ct_obj
	@cd $(DIR_CT)
	$(LINKER) $(LFLAGS) $(LFLAGS_CP) -o $(TARGET_CT) $(NAME_CT).o
	@cd ..

smart_pointers : sp_dir sp_obj
	@cd $(DIR_SP)
	$(LINKER) $(LFLAGS) $(LFLAGS_SP) -o $(TARGET_SP) $(NAME_SP).o
	@cd ..

test_clipp : tc_dir tc_obj
	@cd $(DIR_TC)
	$(LINKER) $(LFLAGS) $(LFLAGS_TC) -o $(TARGET_TC) $(NAME_TC).o
	@cd ..


# Build prerequisites #########################################################

# Dirs
ct_dir:
	@if not exist $(DIR_CT) mkdir $(DIR_CT)

sp_dir:
	@if not exist $(DIR_SP) mkdir $(DIR_SP)

tc_dir:
	@if not exist $(DIR_TC) mkdir $(DIR_TC)


# Compile object files
ct_obj:
	$(CXX) $(CXXFLAGS) -o $(DIR_CT)\$(NAME_CT).o $(NAME_CT).cpp

sp_obj:
	$(CXX) $(CXXFLAGS) -o $(DIR_SP)\$(NAME_SP).o $(NAME_SP).cpp

tc_obj:
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(DIR_TC)\$(NAME_TC).o $(NAME_TC).cpp


# Help menu ###################################################################
help :
	@echo Usage: nmake [OPTION]
	@echo.
	@echo * Help options
	@echo [help] - show this help message and exit
	@echo.
	@echo * Build options
	@echo [containers] - Build "Containers" study case
	@echo [smart_pointers] - Build "Smart Pointers" study case
	@echo [test_clipp] - Build "Test Clipp" study case
	@echo.
	@echo * Cleaning options
	@echo [clean] - clear object files from all previous build
	@echo [clean_containers] - clear object files for the "Containers" study case
	@echo [clean_smart_pointer] - clear object files for the "Smart Pointers" study case
	@echo [clean_test_clipp] - clear object files for the "Test Clipp" study case
	@echo [cleanall] - clear all compiled files from previous builds
	@echo [cleanall_containers] - clear all compiled files for the "Containers" study case
	@echo [cleanall_smart_pointers] - clear all compiled files for the "Smart Pointers" study case
	@echo [cleanall_test_clipp] - clear all compiled files for the "Test Clipp" study case


# Clean intermediate files ####################################################
clean: clean_containers clean_smart_pointers clean_test_clipp

clean_containers :
	@if exist $(DIR_CT) (@del $(DIR_CT)\$(OBJS) $(DIR_CT)\$(PDB_CT) $(DIR_CT)\$(ILKS))

clean_smart_pointers :
	@if exist $(DIR_SP) (@del $(DIR_SP)\$(OBJS) $(DIR_SP)\$(PDB_SP) $(DIR_SP)\$(ILKS))

clean_test_clipp :
	@if exist $(DIR_TC) (@del $(DIR_TC)\$(OBJS) $(DIR_TC)\$(PDB_TC) $(DIR_TC)\$(ILKS))


# Clean everything except sources #############################################
cleanall: cleanall_containers cleanall_smart_pointers cleanall_test_clipp

cleanall_containers :
	@if exist $(DIR_CT) (@rmdir /S /Q $(DIR_CT))

cleanall_smart_pointers :
	@if exist $(DIR_SP) (@rmdir /S /Q $(DIR_SP))

cleanall_test_clipp :
	@if exist $(DIR_TC) (@rmdir /S /Q $(DIR_TC))
