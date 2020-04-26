# Make documentation: http://www.gnu.org/software/make/manual/

SHELL = /bin/bash
CPP   = clang++

NAME = simplehexdump
CAPITALIZED_NAME = Simple Hex Dump Application

FLAGS        = -std=c++11
EXTRAFLAGS   = -v -O0 -g -pedantic -Wall -Wextra -fcolor-diagnostics

TARGET  = $(NAME)
LIBS    = -lboost_program_options
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY : help clean cleanall

$(TARGET) : $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS) $(LIBS)

%.o : %.cpp
	$(CPP) $(FLAGS) $(EXTRAFLAGS) -c $<

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
