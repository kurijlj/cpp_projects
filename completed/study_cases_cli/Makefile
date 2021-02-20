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
NAME_CAST_LOGIC = cast_logical_expressions
NAME_CT = containers
NAME_RN = random_numbers
NAME_SP = smart_pointers
NAME_TC = test_clipp
NAME_VAT = va_list

TARGET_CAST_LOGIC = $(NAME_CAST_LOGIC).exe
TARGET_CT = $(NAME_CT).exe
TARGET_RN = $(NAME_RN).exe
TARGET_SP = $(NAME_SP).exe
TARGET_TC = $(NAME_TC).exe
TARGET_VAT = $(NAME_VAT).exe

PDB_CAST_LOGIC = $(NAME_CAST_LOGIC).pdb
PDB_CT = $(NAME_CT).pdb
PDB_RN = $(NAME_RN).pdb
PDB_SP = $(NAME_SP).pdb
PDB_TC = $(NAME_TC).pdb
PDB_VAT = $(NAME_VAT).pdb

DIR_CAST_LOGIC = .\$(NAME_CAST_LOGIC)
DIR_CT = .\$(NAME_CT)
DIR_RN = .\$(NAME_RN)
DIR_SP = .\$(NAME_SP)
DIR_TC = .\$(NAME_TC)
DIR_VAT = .\$(NAME_VAT)

OBJS = *.o
ILKS = *.ilk
EXPS = *.exp
LIBS = *.lib

CXX = clang++
CXXFLAGS = -c -pipe -std=c++17 -g -O0 -v -pedantic -Wall -Wextra \
		   -fcolor-diagnostics -fdiagnostics-format=vi
LINKER = clang++
LFLAGS = -fcolor-diagnostics

LFLAGS_CAST_LOGIC = -Wl,/debug,/pdb:$(PDB_CAST_LOGIC)
LFLAGS_CT = -Wl,/debug,/pdb:$(PDB_CT)
LFLAGS_RN = -Wl,/debug,/pdb:$(PDB_RN)
LFLAGS_SP = -Wl,/debug,/pdb:$(PDB_SP)
LFLAGS_TC = -Wl,/debug,/pdb:$(PDB_TC)
LFLAGS_VAT = -Wl,/debug,/pdb:$(PDB_VAT)

INCPATH = -I.\include


# Build cases ###################################################################
all : cast_logical_expressions \
	containers \
	random_numbers \
	smart_pointers \
	test_clipp \
	va_list

cast_logical_expressions : cast_logic_dir cast_logic_obj
	@cd $(DIR_CAST_LOGIC)
	$(LINKER) $(LFLAGS) $(LFLAGS_CAST_LOGIC) -o $(TARGET_CAST_LOGIC) \
		$(NAME_CAST_LOGIC).o
	@cd ..

containers : ct_dir ct_obj
	@cd $(DIR_CT)
	$(LINKER) $(LFLAGS) $(LFLAGS_CP) -o $(TARGET_CT) $(NAME_CT).o
	@cd ..

random_numbers : random_numbers_dir random_numbers_obj
	@cd $(DIR_RN)
	$(LINKER) $(LFLAGS) $(LFLAGS_RN) -o $(TARGET_RN) $(NAME_RN).o
	@cd ..

smart_pointers : sp_dir sp_obj
	@cd $(DIR_SP)
	$(LINKER) $(LFLAGS) $(LFLAGS_SP) -o $(TARGET_SP) $(NAME_SP).o
	@cd ..

test_clipp : tc_dir tc_obj
	@cd $(DIR_TC)
	$(LINKER) $(LFLAGS) $(LFLAGS_TC) -o $(TARGET_TC) $(NAME_TC).o
	@cd ..

va_list : va_dir va_obj
	@cd $(DIR_VAT)
	$(LINKER) $(LFLAGS) $(LFLAGS_VAT) -o $(TARGET_VAT) $(NAME_VAT).o
	@cd ..


# Build prerequisites #########################################################

# Dirs
cast_logic_dir:
	@if not exist $(DIR_CAST_LOGIC) mkdir $(DIR_CAST_LOGIC)

ct_dir:
	@if not exist $(DIR_CT) mkdir $(DIR_CT)

random_numbers_dir:
	@if not exist $(DIR_RN) mkdir $(DIR_RN)

sp_dir:
	@if not exist $(DIR_SP) mkdir $(DIR_SP)

tc_dir:
	@if not exist $(DIR_TC) mkdir $(DIR_TC)

va_dir:
	@if not exist $(DIR_VAT) mkdir $(DIR_VAT)


# Compile object files
cast_logic_obj:
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(DIR_CAST_LOGIC)\$(NAME_CAST_LOGIC).o \
		$(NAME_CAST_LOGIC).cpp

ct_obj:
	$(CXX) $(CXXFLAGS) -o $(DIR_CT)\$(NAME_CT).o $(NAME_CT).cpp

random_numbers_obj:
	$(CXX) $(CXXFLAGS) -o $(DIR_RN)\$(NAME_RN).o $(NAME_RN).cpp

sp_obj:
	$(CXX) $(CXXFLAGS) -o $(DIR_SP)\$(NAME_SP).o $(NAME_SP).cpp

tc_obj:
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(DIR_TC)\$(NAME_TC).o $(NAME_TC).cpp

va_obj:
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(DIR_VAT)\$(NAME_VAT).o $(NAME_VAT).cpp


# Help menu ###################################################################
help :
	@echo Usage: nmake [OPTION]
	@echo.
	@echo * Help options
	@echo [help] - show this help message and exit
	@echo.
	@echo * Build options
	@echo [cast_logical_expressions] - Build "Cast to Logical Expressions" \
		study case
	@echo [containers] - Build "Containers" study case
	@echo [random_numbers] - Build "Random Numbers" study case
	@echo [smart_pointers] - Build "Smart Pointers" study case
	@echo [test_clipp] - Build "Test Clipp" study case
	@echo [va_list] - Build "Variadic Function Arguments" study case
	@echo.
	@echo * Cleaning options
	@echo [clean] - clear object files from all previous build
	@echo [clean_cast_logical_expressions] - clear object files for \
		the "Cast to Logical Expressions" study case
	@echo [clean_containers] - clear object files for \
		the "Containers" study case
	@echo [clean_random_numbers] = clear object files for \
		"Random Numbers" study case
	@echo [clean_smart_pointer] - clear object files for \
		the "Smart Pointers" study case
	@echo [clean_test_clipp] - clear object files for the \
		"Test Clipp" study case
	@echo [clean_va_list] - clear object files for \
		the "Variadic Function Arguments" study case
	@echo [cleanall] - clear all compiled files from previous builds
	@echo [cleanall_cast_logical_expressions] - clear all compiled files for \
		the "Cast to Logical Expressions" study case
	@echo [cleanall_containers] - clear all compiled files for \
		the "Containers" study case
	@echo [cleanall_random_numbers] = clear all compiled files for \
		"Random Numbers" study case
	@echo [cleanall_smart_pointers] - clear all compiled files for \
		the "Smart Pointers" study case
	@echo [cleanall_test_clipp] - clear all compiled files for \
		the "Test Clipp" study case
	@echo [cleanall_va_list] - clear all compiled files for \
		the "Variadic Function Arguments" study case


# Clean intermediate files ####################################################
clean: clean_cast_logical_expressions \
	clean_containers \
	clean_random_numbers \
	clean_smart_pointers \
	clean_test_clipp \
	clean_va_list

clean_cast_logical_expressions :
	@if exist $(DIR_CAST_LOGIC) (@del $(DIR_CAST_LOGIC)\$(OBJS) \
		$(DIR_CAST_LOGIC)\$(PDB_CAST_LOGIC) \
		$(DIR_CAST_LOGIC)\$(ILKS))

clean_containers :
	@if exist $(DIR_CT) (@del $(DIR_CT)\$(OBJS) \
		$(DIR_CT)\$(PDB_CT) \
		$(DIR_CT)\$(ILKS))

clean_random_numbers :
	@if exist $(DIR_RN) (@del $(DIR_RN)\$(OBJS) \
		$(DIR_RN)\$(PDB_RN) \
		$(DIR_RN)\$(ILKS))

clean_smart_pointers :
	@if exist $(DIR_SP) (@del $(DIR_SP)\$(OBJS) \
		$(DIR_SP)\$(PDB_SP) \
		$(DIR_SP)\$(ILKS))

clean_test_clipp :
	@if exist $(DIR_TC) (@del $(DIR_TC)\$(OBJS) \
		$(DIR_TC)\$(PDB_TC) \
		$(DIR_TC)\$(ILKS))

clean_va_list :
	@if exist $(DIR_VAT) (@del $(DIR_VAT)\$(OBJS) \
		$(DIR_VAT)\$(PDB_VAT) \
		$(DIR_VAT)\$(ILKS))


# Clean everything except sources #############################################
cleanall: cleanall_cast_logical_expressions \
	cleanall_containers \
	cleanall_random_numbers \
	cleanall_smart_pointers \
	cleanall_test_clipp \
	cleanall_va_list

cleanall_cast_logical_expressions :
	@if exist $(DIR_CAST_LOGIC) (@rmdir /S /Q $(DIR_CAST_LOGIC))

cleanall_containers :
	@if exist $(DIR_CT) (@rmdir /S /Q $(DIR_CT))

cleanall_random_numbers :
	@if exist $(DIR_RN) (@rmdir /S /Q $(DIR_RN))

cleanall_smart_pointers :
	@if exist $(DIR_SP) (@rmdir /S /Q $(DIR_SP))

cleanall_test_clipp :
	@if exist $(DIR_TC) (@rmdir /S /Q $(DIR_TC))

cleanall_va_list :
	@if exist $(DIR_VAT) (@rmdir /S /Q $(DIR_VAT))
