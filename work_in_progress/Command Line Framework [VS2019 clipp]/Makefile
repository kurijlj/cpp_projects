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


NAME = app
TARGET = $(NAME).exe
OBJECTS = *.o

CXX = clang++.exe
CXXFLAGS = -c -pipe -g -std=c++17 -v -O0 -pedantic -Wall -Wextra -fcolor-diagnostics
LINK = clang++.exe

INCPATH = -I.\include
LIBS_USER = 

# Build app
app : main.o validators.o
	$(LINK) -o $(TARGET) main.o validators.o

main.o:
	$(CXX) $(CXXFLAGS) $(INCPATH) main.cpp

validators.o:
	$(CXX) $(CXXFLAGS) $(INCPATH) validators.cpp

# Show help
help :
	@echo Usage: nmake [OPTION]
	@echo [app] - compile code
	@echo [clean] - clear object files from previous build
	@echo [cleanall] - clear all files from previous build
	@echo [help] - show this help message and exit

# Clean intermediate files
clean :
	@del.exe $(OBJECTS)

# Clean everything except sources
cleanall :
	@del.exe $(OBJECTS) $(TARGET)
