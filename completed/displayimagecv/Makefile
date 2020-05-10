# -*-Makefile-*-
# This Makefile is for building: displayimagecv

##  Copyright (C) 2020 Ljubomir Kurij <kurijlj@gmail.com>
##
## This program is free software: you can redistribute it and/or modify
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

SHELL = /bin/bash
CC    = clang
CPP   = clang++

NAME = displayimagecv
CAPITALIZED_NAME = Display Image OpenCV

FLAGS        = -std=c++11
EXTRAFLAGS   = -v -O0 -g -pedantic -Wall -Wextra -fcolor-diagnostics
EXTRAFLAGS  += `pkg-config --cflags opencv`

TARGET   = $(NAME)
LIBS     = -lboost_program_options
LIBS    += `pkg-config --libs opencv`
SOURCES  = $(wildcard *.cpp)
COMMON   =
HEADERS  =
OBJECTS  = $(SOURCES:.cpp=.o)

.PHONY : help clean cleanall

$(TARGET) : $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS) $(LIBS)

%.o : %.cpp
	$(CPP) -c $(FLAGS) $(EXTRAFLAGS) $<

help :
	@echo -e "Usage: make [OPTION]\n"
	@echo -e "  \"EXTRAFLAGS = -O2 -w\"    compile release version"
	@echo -e "  clean                    clear object files from previous build"
	@echo -e "  cleanall                 clear all files from previous build"
	@echo -e "  help                     show this help message and exit\n"
	@echo -e "To echo output form compiler to log file use:"
	@echo -e "  make [OPTION] 2>&1 | tee <filename>\n"

clean:
	-rm -vf $(OBJECTS)

cleanall: clean
	-rm -vf $(TARGET)
